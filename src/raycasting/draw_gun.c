/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:32:33 by vdeliere          #+#    #+#             */
/*   Updated: 2025/08/07 13:20:05 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * put_gun_pixel - Place un pixel de l'arme dans l'image principale
 * @g: Pointeur vers la structure de jeu contenant les données d'image
 * @x: Coordonnée X du pixel à placer sur l'écran
 * @y: Coordonnée Y du pixel à placer sur l'écran
 * @color: Couleur du pixel au format ARGB (32 bits)
 *
 * Cette fonction place directement un pixel coloré aux coordonnées (x,y)
 * dans le buffer d'image principal de la fenêtre. Elle effectue d'abord
 * une vérification des limites pour s'assurer que le pixel est dans les
 * bornes de l'écran (WIDTH x HEIGHT). Si les coordonnées sont valides,
 * elle calcule l'adresse mémoire du pixel dans le buffer d'image en
 * utilisant la formule: adresse = base + (y * largeur_ligne + x * bpp/8)
 * où bpp est le nombre de bits par pixel.
 */
static void	put_gun_pixel(t_game *g, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = g->img_data + (y * g->size_line + x * (g->bpp / 8));
	*(unsigned int *)pixel = color;
}

/**
 * get_gun_pixel_from_data - Récupère la couleur d'un pixel depuis les données
 *                           de texture de l'arme
 * @tex_data: Pointeur vers les données brutes de la texture de l'arme
 * @gun_x: Coordonnée X du pixel dans la texture de l'arme
 * @gun_y: Coordonnée Y du pixel dans la texture de l'arme
 * @g: Pointeur vers la structure de jeu contenant les informations de texture
 *
 * Return: La couleur du pixel au format ARGB, ou 0xFF00FF (magenta) en cas
 *         d'erreur
 *
 * Cette fonction extrait la couleur d'un pixel spécifique des données de
 * texture de l'arme. Elle vérifie d'abord que les données de texture sont
 * valides et que les coordonnées demandées sont dans les limites de la
 * texture. Si une erreur est détectée (données nulles ou coordonnées hors
 * limites), elle retourne une couleur magenta (0xFF00FF) pour faciliter
 * le débogage. Sinon, elle calcule l'adresse du pixel dans les données
 * de texture et retourne sa couleur.
 */
static unsigned int	get_gun_pixel_from_data(char *tex_data, int gun_x,
	int gun_y, t_game *g)
{
	char	*pixel;

	if (!tex_data || gun_x < 0 || gun_x >= g->gun.tex_width
		|| gun_y < 0 || gun_y >= g->gun.tex_height)
		return (0xFF00FF);
	pixel = tex_data + (gun_y * g->gun.tex_size_line
			+ gun_x * (g->gun.tex_bpp / 8));
	return (*(unsigned int *)pixel);
}

/**
 * draw_gun - Affiche l'arme du joueur en bas de l'écran
 * @g: Pointeur vers la structure de jeu contenant toutes les données
 *     nécessaires (texture de l'arme, buffer d'image, etc.)
 *
 * Cette fonction est responsable de l'affichage de l'arme du joueur dans
 * l'interface de jeu. Elle parcourt pixel par pixel la texture de l'arme
 * et la dessine dans la partie inférieure de l'écran. L'arme est centrée
 * horizontalement avec un décalage de 150 pixels vers la droite pour un
 * positionnement optimal.
 *
 * Fonctionnement:
 * - Vérifie que les données de texture de l'arme sont disponibles
 * - Calcule la position de départ (bas de l'écran, centrée + offset)
 * - Parcourt chaque pixel de la texture de l'arme
 * - Ignore les pixels de couleur transparente (#00A2E8) et noire
 * - Utilise put_gun_pixel() pour dessiner chaque pixel valide
 *
 * La couleur #00A2E8 (bleu clair) est utilisée comme couleur de
 * transparence dans la texture de l'arme, permettant de ne dessiner
 * que les parties visibles de l'arme sans fond.
 */
void	draw_gun(t_game *g)
{
	int				screen_x;
	int				screen_y;
	int				gun_x;
	int				gun_y;
	unsigned int	color;

	if (!g->gun.tex_data)
		return ;
	screen_y = HEIGHT - g->gun.tex_height;
	gun_y = -1;
	while (++gun_y < g->gun.tex_height)
	{
		screen_x = (WIDTH - g->gun.tex_width) / 2 + 150;
		gun_x = -1;
		while (++gun_x < g->gun.tex_width)
		{
			color = get_gun_pixel_from_data(g->gun.tex_data, gun_x, gun_y, g);
			if (color != 0x00A2E8 && (color & 0xFFFFFF) != 0)
				put_gun_pixel(g, screen_x, screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}
