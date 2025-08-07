/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:26:32 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:30:34 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * load_first_sprite - Charge la première frame d'animation du sprite NPC
 * @game: Pointeur vers la structure de jeu contenant les données MLX
 *
 * Cette fonction charge la première image de l'animation de marche du
 * cochon en utilisant la MLX. Elle :
 * 1. Charge l'image XPM depuis le fichier avec mlx_xpm_file_to_image()
 * 2. Récupère les dimensions (largeur et hauteur) de l'image
 * 3. Obtient l'adresse des données de l'image avec mlx_get_data_addr()
 * 4. Stocke les informations de format (bpp, size_line, endian)
 *
 * Cette première frame est utilisée comme frame de base de l'animation
 * et est stockée dans sprite[0]. En cas d'échec de chargement, l'image
 * reste NULL et les données ne sont pas récupérées.
 */
static void	load_first_sprite(t_game *game)
{
	game->sprite[0].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/xpm/npc/pig_walking.xpm",
			&game->sprite[0].width, &game->sprite[0].height);
	if (game->sprite[0].img)
	{
		game->sprite[0].img_data = mlx_get_data_addr(game->sprite[0].img,
				&game->sprite[0].bpp, &game->sprite[0].size_line,
				&game->sprite[0].endian);
	}
}

/**
 * load_second_sprite - Charge la deuxième frame d'animation du sprite NPC
 * @game: Pointeur vers la structure de jeu contenant les données MLX
 *
 * Cette fonction charge la deuxième image de l'animation de marche du
 * cochon (pig_walking_2.xpm) suivant le même processus que la première
 * frame. Elle stocke l'image dans sprite[1] et constitue la frame
 * intermédiaire de l'animation de marche. Le chargement des données
 * d'image n'est effectué qu'en cas de succès du chargement de l'image
 * elle-même, assurant la cohérence des données.
 */
static void	load_second_sprite(t_game *game)
{
	game->sprite[1].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/xpm/npc/pig_walking_2.xpm",
			&game->sprite[1].width, &game->sprite[1].height);
	if (game->sprite[1].img)
	{
		game->sprite[1].img_data = mlx_get_data_addr(game->sprite[1].img,
				&game->sprite[1].bpp, &game->sprite[1].size_line,
				&game->sprite[1].endian);
	}
}

/**
 * load_third_sprite - Charge la troisième frame d'animation du sprite NPC
 * @game: Pointeur vers la structure de jeu contenant les données MLX
 *
 * Cette fonction charge la troisième et dernière image de l'animation
 * de marche du cochon (pig_walking_3.xpm). Elle complète la séquence
 * d'animation en stockant l'image dans sprite[2]. Cette frame finale
 * permet de créer un cycle d'animation fluide lorsqu'elle est combinée
 * avec les deux autres frames. Le processus de chargement est identique
 * aux autres frames avec vérification de succès avant récupération
 * des données d'image.
 */
static void	load_third_sprite(t_game *game)
{
	game->sprite[2].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/xpm/npc/pig_walking_3.xpm",
			&game->sprite[2].width, &game->sprite[2].height);
	if (game->sprite[2].img)
	{
		game->sprite[2].img_data = mlx_get_data_addr(game->sprite[2].img,
				&game->sprite[2].bpp,
				&game->sprite[2].size_line, &game->sprite[2].endian);
	}
}

/**
 * load_pig_sprite - Charge toutes les frames d'animation du sprite cochon
 * @game: Pointeur vers la structure de jeu contenant les données MLX
 *
 * Cette fonction principale orchestre le chargement complet de l'animation
 * du cochon en appelant séquentiellement les fonctions de chargement
 * individuel. Elle charge les trois frames d'animation :
 * 1. pig_walking.xpm (frame de base)
 * 2. pig_walking_2.xpm (frame intermédiaire) 
 * 3. pig_walking_3.xpm (frame finale)
 *
 * Cette fonction doit être appelée après l'initialisation de la MLX
 * et avant le début de la boucle de jeu. Elle prépare toutes les
 * ressources nécessaires pour l'animation des NPCs cochons dans le jeu.
 * En cas d'échec de chargement d'une frame, celle-ci restera NULL
 * mais n'empêchera pas le chargement des autres.
 */
void	load_pig_sprite(t_game *game)
{
	load_first_sprite(game);
	load_second_sprite(game);
	load_third_sprite(game);
}
