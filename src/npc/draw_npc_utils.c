/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:03 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:41:01 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * get_pixel_from_sprite - Extrait la couleur d'un pixel depuis un sprite
 * @sprite: Pointeur vers la structure sprite contenant les données d'image
 * @x: Coordonnée X du pixel dans le sprite
 * @y: Coordonnée Y du pixel dans le sprite
 *
 * Return: Couleur du pixel au format ARGB, ou 0 si coordonnées invalides
 *
 * Cette fonction fondamentale accède aux données brutes d'un sprite pour
 * récupérer la couleur d'un pixel spécifique. Elle :
 * 1. Vérifie que les coordonnées sont dans les limites du sprite
 * 2. Calcule l'index dans les données d'image avec la formule :
 *    index = y * size_line + x * (bpp / 8)
 * 3. Lit la couleur depuis les données brutes de l'image
 * 4. Retourne la couleur au format ARGB 32 bits
 *
 * Cette fonction est critique pour le système de rendu car elle interface
 * directement avec les données MLX. Elle gère les différents formats
 * d'image en utilisant bpp (bits per pixel) et size_line pour s'adapter
 * automatiquement à la structure interne des images chargées.
 */
int	get_pixel_from_sprite(t_sprite *sprite, int x, int y)
{
	int	color;
	int	index;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
		return (0);
	index = y * sprite->size_line + x * (sprite->bpp / 8);
	color = *(unsigned int *)(sprite->img_data + index);
	return (color);
}

/**
 * is_transparent_pixel - Détermine si un pixel doit être transparent
 * @color: Couleur du pixel au format ARGB à analyser
 *
 * Return: 1 si le pixel est transparent, 0 s'il est opaque
 *
 * Cette fonction implémente la logique de transparence pour les sprites
 * en vérifiant deux conditions de transparence :
 * 1. Transparence alpha : si le canal alpha est 0 (complètement transparent)
 * 2. Couleur clé magenta : si la couleur est 0x00FF00FF (magenta pur)
 *
 * Le magenta (0xFF00FF) est utilisé comme couleur de transparence
 * conventionnelle dans les textures de sprites, permettant aux artistes
 * de définir facilement les zones transparentes. Cette approche double
 * assure la compatibilité avec différents formats d'image et méthodes
 * de création de sprites. Les pixels transparents ne sont pas dessinés,
 * permettant au fond de rester visible.
 */
int	is_transparent_pixel(int color)
{
	unsigned char	alpha;

	alpha = (color >> 24) & 0xFF;
	if (alpha == 0)
		return (1);
	if ((color & 0x00FFFFFF) == 0x00FF00FF)
		return (1);
	return (0);
}

/**
 * draw_sprite_column - Dessine toutes les colonnes d'un sprite simple
 * @game: Pointeur vers la structure de jeu
 * @sprite_screen_x: Position X du centre du sprite sur l'écran
 * @sprite_height: Hauteur du sprite en pixels
 * @sprite_width: Largeur du sprite en pixels
 *
 * Cette fonction de niveau intermédiaire gère le rendu complet d'un
 * sprite en coordonnant le dessin de toutes ses colonnes verticales.
 * Processus :
 * 1. Initialise les limites de rendu avec init_sprite_bounds()
 * 2. Parcourt chaque colonne X du sprite à dessiner
 * 3. Appelle draw_sprite_pixel() pour chaque colonne
 * 4. Incrémente la position de colonne (stripe)
 *
 * Cette approche colonne par colonne est typique du rendu de sprites
 * dans les moteurs 3D style raycasting, permettant un contrôle précis
 * de chaque bande verticale. Elle est utilisée pour les sprites qui
 * n'ont pas besoin de Z-buffer (éléments d'interface, effets au
 * premier plan, etc.).
 */
void	draw_sprite_column(t_game *game, int sprite_screen_x,
						int sprite_height, int sprite_width)
{
	t_sprite_draw	draw;

	init_sprite_bounds(&draw, sprite_screen_x, sprite_height, sprite_width);
	draw.stripe = draw.draw_start_x;
	while (draw.stripe < draw.draw_end_x)
	{
		draw_sprite_pixel(game, &draw, sprite_height, sprite_width);
		draw.stripe++;
	}
}

/**
 * draw_sprite_column_with_zbuffer - Dessine un sprite avec test de profondeur
 * @game: Pointeur vers la structure de jeu contenant le Z-buffer
 * @draw: Structure de dessin Z-buffer pré-configurée
 * @sprite_height: Hauteur du sprite en pixels
 * @sprite_width: Largeur du sprite en pixels
 *
 * Cette fonction avancée gère le rendu d'un sprite en intégrant les tests
 * de profondeur Z-buffer pour un affichage correct dans la scène 3D.
 * Processus :
 * 1. Initialise les limites de rendu avec init_zbuffer_bounds()
 * 2. Parcourt chaque colonne X du sprite
 * 3. Teste la profondeur : sprite_distance + 0.1 < z_buffer[stripe]
 * 4. Dessine la colonne seulement si elle est visible (plus proche)
 * 5. Utilise draw_zbuffer_pixel() pour le rendu final
 *
 * Le décalage de 0.1 dans le test de profondeur évite les problèmes
 * de Z-fighting (scintillement) quand des objets sont à la même distance.
 * Cette fonction est essentielle pour l'intégration correcte des sprites
 * dans l'environnement 3D, assurant qu'ils apparaissent devant/derrière
 * les murs selon leur position réelle.
 */
void	draw_sprite_column_with_zbuffer(t_game *game, t_zbuffer_draw *draw,
									int sprite_height, int sprite_width)
{
	init_zbuffer_bounds(draw, draw->sprite_screen_x, sprite_height,
		sprite_width);
	draw->stripe = draw->draw_start_x;
	while (draw->stripe < draw->draw_end_x)
	{
		if (draw->sprite_distance + 0.1 < game->z_buffer[draw->stripe])
			draw_zbuffer_pixel(game, draw, sprite_height, sprite_width);
		draw->stripe++;
	}
}

/**
 * calculate_sprite_transform - Transforme les coordonnées monde en espace caméra
 * @game: Pointeur vers la structure de jeu contenant les données de caméra
 * @npc: Pointeur vers le NPC à transformer
 * @trans_x: Pointeur pour stocker la coordonnée X transformée
 * @trans_y: Pointeur pour stocker la coordonnée Y transformée (profondeur)
 *
 * Cette fonction cruciale effectue la transformation géométrique des
 * coordonnées mondiales du sprite vers l'espace caméra pour le rendu 3D.
 * Algorithme :
 * 1. Calcule le vecteur relatif sprite->joueur (sprite_x, sprite_y)
 * 2. Calcule l'inverse du déterminant de la matrice de transformation
 * 3. Applique la transformation inverse de la matrice caméra
 * 4. Stocke les coordonnées transformées dans trans_x et trans_y
 *
 * La transformation utilise les vecteurs de direction (dir_x, dir_y) et
 * de plan de la caméra (plane_x, plane_y) pour projeter le sprite dans
 * l'espace de vue. trans_x détermine la position horizontale à l'écran,
 * trans_y représente la profondeur (positive = devant la caméra).
 * Cette transformation est fondamentale pour le rendu perspectif correct.
 */
void	calculate_sprite_transform(t_game *game, t_npc *npc,
		double *trans_x, double *trans_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = npc->x - game->player.x;
	sprite_y = npc->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*trans_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	*trans_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
}
