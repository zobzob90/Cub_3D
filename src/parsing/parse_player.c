/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:17:17 by vdeliere          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * is_player_char - Vérifie si un caractère représente une position de joueur
 * @c: Caractère à vérifier
 *
 * Return: 1 si le caractère est une orientation de joueur valide, 0 sinon
 *
 * Cette fonction détermine si un caractère correspond à une position et
 * orientation valide du joueur dans la carte. Les caractères valides sont :
 * - 'N' : joueur orienté vers le Nord
 * - 'S' : joueur orienté vers le Sud  
 * - 'E' : joueur orienté vers l'Est
 * - 'W' : joueur orienté vers l'Ouest
 * Ces caractères définissent à la fois la position de départ du joueur
 * et sa direction initiale de regard.
 */
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/**
 * set_player_position - Configure la position et l'orientation du joueur
 * @map: Pointeur vers la structure de carte
 * @i: Coordonnée Y (ligne) de la position du joueur
 * @j: Coordonnée X (colonne) de la position du joueur
 *
 * Cette fonction initialise les paramètres du joueur basés sur sa position
 * trouvée dans la grille. Elle :
 * 1. Définit les coordonnées monde du joueur (centre de la cellule)
 * 2. Sauvegarde l'orientation initiale du joueur
 * 3. Remplace le caractère du joueur par '0' (cellule vide walkable)
 *
 * Les coordonnées sont converties en coordonnées monde en ajoutant 0.5
 * pour centrer le joueur dans sa cellule. L'orientation est préservée
 * pour l'initialisation ultérieure de la direction de vue.
 */
static void	set_player_position(t_map *map, int i, int j)
{
	map->player.x = (double)j + 0.5;
	map->player.y = (double)i + 0.5;
	map->player.orientation = map->grid[i][j];
	map->grid[i][j] = '0';
}

/**
 * find_player - Localise et configure le joueur dans la carte
 * @map: Pointeur vers la structure de carte contenant la grille
 *
 * Return: 1 si exactement un joueur est trouvé, 0 sinon
 *
 * Cette fonction parcourt entièrement la grille de la carte pour localiser
 * le joueur et valider qu'il n'y en a qu'un seul. Elle :
 * 1. Examine chaque cellule de la grille
 * 2. Compte les occurrences de caractères de joueur (N/S/E/W)
 * 3. Configure la position du joueur via set_player_position()
 * 4. Vérifie qu'exactement un joueur est présent
 *
 * La validation est cruciale car le jeu ne peut fonctionner qu'avec
 * exactement un joueur : aucun joueur ou plusieurs joueurs constituent
 * une erreur de configuration de carte. Retourne 0 si le nombre de
 * joueurs trouvés n'est pas égal à 1.
 */
int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player_char(map->grid[i][j]))
			{
				set_player_position(map, i, j);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}
