/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:45:00 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:40:31 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * calculate_sprite_distance - Calcule la distance entre NPC et joueur
 * @npc: Pointeur vers le NPC dont on veut calculer la distance
 * @player: Pointeur vers le joueur servant de référence
 *
 * Return: Distance euclidienne entre le NPC et le joueur
 *
 * Cette fonction utilitaire calcule la distance réelle dans l'espace 2D
 * entre un NPC et le joueur en utilisant le théorème de Pythagore.
 * Elle est utilisée pour :
 * 1. Déterminer si un NPC doit être rendu (culling par distance)
 * 2. Éviter les artefacts visuels quand le joueur est très proche
 * 3. Calculer les priorités de rendu pour l'optimisation
 *
 * La formule utilisée est : distance = √(dx² + dy²)
 * où dx et dy sont les différences de coordonnées entre le NPC et le joueur.
 * Cette distance est cruciale pour maintenir la cohérence visuelle du
 * système de rendu 3D.
 */
double	calculate_sprite_distance(t_npc *npc, t_player *player)
{
	double	dx;
	double	dy;

	dx = npc->x - player->x;
	dy = npc->y - player->y;
	return (sqrt(dx * dx + dy * dy));
}

/**
 * setup_sprite_draw - Configure les paramètres de rendu d'un sprite
 * @draw: Structure de dessin Z-buffer à initialiser
 * @npc: NPC à dessiner (source des données d'animation)
 * @sprite_screen_x: Position X calculée du sprite sur l'écran
 * @transform_y: Distance transformée du sprite (profondeur Z)
 *
 * Cette fonction prépare la structure de rendu avec les paramètres
 * essentiels pour le dessin d'un sprite avec Z-buffer. Elle configure :
 * 1. La position horizontale du sprite sur l'écran
 * 2. La distance de profondeur pour les tests Z-buffer
 * 3. La frame d'animation courante du NPC
 *
 * Ces paramètres sont ensuite utilisés par les fonctions de rendu
 * pour dessiner correctement le sprite avec la bonne animation et
 * la gestion de profondeur appropriée. La distance transform_y est
 * particulièrement importante car elle détermine si le sprite doit
 * apparaître devant ou derrière d'autres éléments de la scène.
 */
void	setup_sprite_draw(t_zbuffer_draw *draw, t_npc *npc,
	int sprite_screen_x, double transform_y)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->sprite_distance = transform_y;
	draw->anim_frame = npc->anim_frame;
}

/**
 * render_zbuffer_column - Rend une colonne de sprite avec test Z-buffer
 * @game: Pointeur vers la structure de jeu contenant les sprites
 * @draw: Structure de dessin contenant les paramètres de rendu
 * @sprite_height: Hauteur du sprite à l'écran en pixels
 * @tex_x: Coordonnée X de la texture à utiliser
 *
 * Cette fonction critique effectue le rendu d'une colonne verticale de
 * sprite en intégrant les tests de profondeur Z-buffer. Processus :
 * 1. Parcourt chaque pixel Y de la colonne à dessiner
 * 2. Calcule la coordonnée Y de texture avec transformation perspective
 * 3. Récupère la couleur du pixel depuis la texture d'animation courante
 * 4. Filtre les couleurs transparentes (magenta 0xFF00FF et noir 0x000000)
 * 5. Dessine le pixel en utilisant put_pixel_to_img()
 *
 * La formule de transformation Y utilise un facteur 256 pour la précision
 * et intègre la hauteur du sprite et de l'écran pour maintenir les
 * proportions correctes. Les masques de couleur (0x00FFFFFF) ignorent
 * le canal alpha pour la comparaison de transparence.
 */
void	render_zbuffer_column(t_game *game, t_zbuffer_draw *draw,
	int sprite_height, int tex_x)
{
	int	d;
	int	tex_y;
	int	color;

	draw->y = draw->draw_start_y;
	while (draw->y < draw->draw_end_y)
	{
		d = draw->y * 256 - HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * game->sprite[draw->anim_frame].height)
				/ sprite_height) / 256;
		if (tex_y >= 0 && tex_y < game->sprite[draw->anim_frame].height)
		{
			color = get_pixel_from_sprite(&game->sprite[draw->anim_frame],
					tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0x00FF00FF
				&& (color & 0x00FFFFFF) != 0x00000000)
				put_pixel_to_img(game, draw->stripe, draw->y, color);
		}
		draw->y++;
	}
}

/**
 * init_sprite_bounds - Initialise les limites de rendu d'un sprite simple
 * @draw: Structure de dessin à configurer
 * @sprite_screen_x: Position X du centre du sprite sur l'écran
 * @sprite_height: Hauteur du sprite en pixels
 * @sprite_width: Largeur du sprite en pixels
 *
 * Cette fonction calcule et définit les limites de rendu pour un sprite
 * sans Z-buffer, utilisée pour les sprites plus simples ou les cas
 * d'optimisation. Elle :
 * 1. Centre le sprite verticalement sur l'écran (HEIGHT / 2)
 * 2. Centre le sprite horizontalement sur sprite_screen_x
 * 3. Applique le clipping aux limites de l'écran
 * 4. Calcule les limites de début et fin pour X et Y
 *
 * Contrairement à init_zbuffer_bounds(), cette fonction ne fait pas
 * de décalage vertical pour l'effet "au sol", centrant parfaitement
 * le sprite. Elle est utilisée pour des sprites flottants ou des
 * effets spéciaux qui ne doivent pas paraître posés au sol.
 * Les vérifications de limites préviennent tout dépassement de buffer.
 */
void	init_sprite_bounds(t_sprite_draw *draw, int sprite_screen_x,
	int sprite_height, int sprite_width)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}
