/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:26:42 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:36:49 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * draw_sprite_pixel - Dessine une colonne de pixels d'un sprite NPC
 * @game: Pointeur vers la structure de jeu contenant les données de sprite
 * @draw: Structure contenant les paramètres de dessin (position, limites)
 * @sprite_height: Hauteur calculée du sprite à l'écran
 * @sprite_width: Largeur calculée du sprite à l'écran
 *
 * Cette fonction rend une colonne verticale d'un sprite NPC en appliquant
 * une transformation de texture. Elle :
 * 1. Calcule la coordonnée X de texture en fonction de la position à l'écran
 * 2. Utilise un facteur d'échelle de 256 pour la précision des calculs
 * 3. Parcourt chaque pixel Y de la colonne à dessiner
 * 4. Calcule la coordonnée Y de texture avec une formule de perspective
 * 5. Récupère la couleur du pixel depuis la texture du sprite
 * 6. Filtre les couleurs transparentes (magenta 0xFF00FF et noir 0x000000)
 * 7. Dessine le pixel dans l'image finale si il n'est pas transparent
 *
 * La formule de transformation Y intègre la perspective 3D pour un rendu
 * réaliste du sprite dans l'espace 3D du jeu.
 */
void	draw_sprite_pixel(t_game *game, t_sprite_draw *draw,
	int sprite_height, int sprite_width)
{
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;
	int	temp_calc;

	temp_calc = draw->stripe - (-sprite_width / 2 + draw->sprite_screen_x);
	tex_x = (int)(256 * temp_calc * game->sprite[0].width / sprite_width) / 256;
	if (tex_x < 0 || tex_x >= game->sprite[0].width)
		return ;
	draw->y = draw->draw_start_y;
	while (draw->y < draw->draw_end_y)
	{
		d = draw->y * 256 - HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * game->sprite[0].height) / sprite_height) / 256;
		if (tex_y >= 0 && tex_y < game->sprite[0].height)
		{
			color = get_pixel_from_sprite(&game->sprite[0], tex_x, tex_y);
			if (color != 0xFF00FF && color != 0x000000
				&& (color & 0xFF000000) != 0)
				put_pixel_to_img(game, draw->stripe, draw->y, color);
		}
		draw->y++;
	}
}

/**
 * init_zbuffer_bounds - Initialise les limites de rendu pour le Z-buffer
 * @draw: Structure de dessin à initialiser avec les limites calculées
 * @sprite_screen_x: Position X du sprite sur l'écran
 * @sprite_height: Hauteur du sprite à l'écran
 * @sprite_width: Largeur du sprite à l'écran
 *
 * Cette fonction calcule et définit les limites de rendu d'un sprite pour
 * optimiser les performances et éviter les dépassements de buffer. Elle :
 * 1. Définit la position centrale du sprite (sprite_screen_x)
 * 2. Calcule les limites Y avec un décalage vertical (sprite_height / 8)
 * 3. Calcule les limites X centrées sur la position du sprite
 * 4. Applique le clipping aux limites de l'écran (0 à WIDTH/HEIGHT-1)
 *
 * Le décalage vertical (sprite_height / 8) permet de positionner le sprite
 * légèrement plus bas pour simuler qu'il "touche le sol" plutôt que de
 * flotter au centre de l'écran. Les vérifications de limites empêchent
 * tout dépassement de buffer lors du rendu, assurant la stabilité du
 * programme même avec des sprites partiellement hors écran.
 */
void	init_zbuffer_bounds(t_zbuffer_draw *draw, int sprite_screen_x,
							int sprite_height, int sprite_width)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->draw_start_y = -sprite_height / 2 + HEIGHT / 2 + sprite_height / 8;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = sprite_height / 2 + HEIGHT / 2 + sprite_height / 8;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}

/**
 * draw_zbuffer_pixel - Dessine une colonne de sprite avec test de profondeur
 * @game: Pointeur vers la structure de jeu
 * @draw: Structure de dessin contenant les paramètres et frame d'animation
 * @sprite_height: Hauteur du sprite à l'écran
 * @sprite_width: Largeur du sprite à l'écran
 *
 * Cette fonction optimisée gère le rendu d'une colonne de sprite en
 * utilisant le Z-buffer pour la gestion de profondeur. Elle :
 * 1. Calcule la coordonnée X de texture pour la frame d'animation courante
 * 2. Utilise le même algorithme de transformation que draw_sprite_pixel
 * 3. Vérifie les limites de la texture pour éviter les accès invalides
 * 4. Délègue le rendu de la colonne à render_zbuffer_column()
 *
 * La différence principale avec draw_sprite_pixel est l'utilisation de
 * draw->anim_frame pour sélectionner la bonne texture d'animation,
 * permettant l'affichage de sprites animés. Le test de profondeur est
 * géré dans render_zbuffer_column() pour s'assurer que les sprites
 * apparaissent correctement devant/derrière les murs.
 */
void	draw_zbuffer_pixel(t_game *game, t_zbuffer_draw *draw,
	int sprite_height, int sprite_width)
{
	int	tex_x;
	int	temp_calc;

	temp_calc = draw->stripe - (-sprite_width / 2 + draw->sprite_screen_x);
	tex_x = (int)(256 * temp_calc * game->sprite[draw->anim_frame].width
			/ sprite_width) / 256;
	if (tex_x < 0 || tex_x >= game->sprite[draw->anim_frame].width)
		return ;
	render_zbuffer_column(game, draw, sprite_height, tex_x);
}

/**
 * draw_single_npc - Effectue le rendu complet d'un NPC individuel
 * @game: Pointeur vers la structure de jeu contenant caméra et données
 * @npc: Pointeur vers le NPC à dessiner
 *
 * Cette fonction principale orchestre le rendu d'un NPC en appliquant
 * toute la pipeline de rendu 3D. Processus :
 * 1. Calcule la transformation monde->caméra avec calculate_sprite_transform()
 * 2. Vérifie que le sprite est devant la caméra (transform_y > 0)
 * 3. Vérifie la distance minimale pour éviter les effets visuels bizarres
 * 4. Projette la position 3D sur l'écran 2D
 * 5. Calcule la taille du sprite selon la distance (perspective)
 * 6. Effectue le culling de frustum (sprite partiellement/totalement visible)
 * 7. Configure les paramètres de rendu avec setup_sprite_draw()
 * 8. Lance le rendu avec Z-buffer via draw_sprite_column_with_zbuffer()
 *
 * Le facteur 0.7 dans le calcul de taille ajuste l'échelle visuelle des
 * sprites. La distance minimale de 0.1 empêche les artefacts visuels
 * quand le joueur est très proche d'un NPC.
 */
static void	draw_single_npc(t_game *game, t_npc *npc)
{
	double			transform_x;
	double			transform_y;
	t_zbuffer_draw	draw;
	int				sprite_screen_x;
	int				sprite_size;

	calculate_sprite_transform(game, npc, &transform_x, &transform_y);
	if (transform_y > 0 && calculate_sprite_distance(npc, &game->player) > 0.1)
	{
		sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
		sprite_size = abs((int)(HEIGHT / transform_y * 0.7));
		if (sprite_screen_x > -sprite_size
			&& sprite_screen_x < WIDTH + sprite_size)
		{
			setup_sprite_draw(&draw, npc, sprite_screen_x, transform_y);
			draw_sprite_column_with_zbuffer(game, &draw, sprite_size,
				sprite_size);
		}
	}
}

/**
 * draw_npcs_sprites - Dessine tous les NPCs présents dans le jeu
 * @game: Pointeur vers la structure de jeu contenant la carte et les NPCs
 *
 * Cette fonction de haut niveau gère le rendu de tous les NPCs du jeu
 * en une seule passe. Elle :
 * 1. Parcourt séquentiellement tous les NPCs de la carte
 * 2. Appelle draw_single_npc() pour chaque NPC valide
 * 3. Utilise le nombre total de NPCs (num_npcs) comme limite de boucle
 *
 * Cette fonction doit être appelée après le rendu des murs mais avant
 * le rendu de l'interface utilisateur pour respecter l'ordre de
 * profondeur. Le Z-buffer intégré dans draw_single_npc() s'assure
 * que chaque NPC apparaît correctement dans la scène 3D, devant ou
 * derrière les murs selon sa position relative.
 *
 * L'ordre de rendu des NPCs entre eux n'est pas critique car le
 * Z-buffer gère automatiquement la visibilité correcte.
 */
void	draw_npcs_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->num_npcs)
	{
		draw_single_npc(game, &game->map->npcs[i]);
		i++;
	}
}
