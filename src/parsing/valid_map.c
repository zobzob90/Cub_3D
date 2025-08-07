/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:13:33 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * check_borders - Vérifie que les bordures horizontales de la carte sont valides
 * @map: Pointeur vers la structure de carte contenant la grille
 *
 * Return: true si les bordures sont valides, false sinon
 *
 * Cette fonction valide que la première et la dernière ligne de la carte
 * ne contiennent que des murs ('1') ou des espaces (' '). Ces bordures
 * horizontales sont essentielles pour empêcher le joueur de sortir de
 * la carte. La fonction parcourt :
 * - Ligne 0 (bordure supérieure) : chaque colonne de 0 à width-1
 * - Ligne height-1 (bordure inférieure) : chaque colonne de 0 à width-1
 *
 * Tout caractère autre que '1' ou ' ' dans ces bordures invalide la carte
 * car cela créerait une "fuite" permettant au joueur de sortir de l'aire
 * de jeu délimitée.
 */
static bool	check_borders(t_map *map)
{
	int	i;
	int	widht;
	int	height;

	i = 0;
	widht = map->width;
	height = map->height;
	while (i < widht)
	{
		if (map->grid[0][i] != '1' && map->grid[0][i] != ' ')
			return (false);
		i++;
	}
	i = 0;
	while (i < widht)
	{
		if (map->grid[height - 1][i] != '1' && map->grid[height - 1][i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

/**
 * check_sides - Vérifie que les bordures verticales de la carte sont valides
 * @map: Pointeur vers la structure de carte contenant la grille
 *
 * Return: true si les bordures latérales sont valides, false sinon
 *
 * Cette fonction valide que les bordures gauche et droite de chaque ligne
 * de la carte ne contiennent que des murs ('1') ou des espaces (' ').
 * Pour chaque ligne de la carte :
 * - Vérifie le premier caractère (colonne 0)
 * - Vérifie le dernier caractère (colonne width-1)
 *
 * La validation des bordures verticales complète celle des bordures
 * horizontales pour s'assurer que la carte est complètement fermée.
 * Les espaces sont autorisés en bordure car ils représentent des zones
 * non-walkables qui agissent comme des murs naturels.
 */
static bool	check_sides(t_map *map)
{
	int	y;
	int	width;
	int	height;

	height = map->height;
	y = 0;
	while (y < height)
	{
		width = ft_strlen(map->grid[y]);
		if (map->grid[y][0] != '1' && map->grid[y][0] != ' ')
			return (false);
		if (map->grid[y][width - 1] != '1' && map->grid[y][width - 1] != ' ')
			return (false);
		y++;
	}
	return (true);
}

/**
 * check_inside - Vérifie l'intégrité interne de la carte
 * @map: Pointeur vers la structure de carte contenant la grille
 *
 * Return: true si l'intérieur de la carte est valide, false sinon
 *
 * Cette fonction critique valide que toutes les cellules walkables à
 * l'intérieur de la carte sont correctement entourées. Elle parcourt
 * toutes les cellules internes (excluant les bordures) et pour chaque
 * cellule walkable ('0', 'N', 'S', 'E', 'W', 'O', 'X', 'D') vérifie
 * qu'aucune cellule adjacente (haut, bas, gauche, droite) n'est un espace.
 *
 * Cette vérification empêche les "fuites" dans la carte où le joueur
 * pourrait accéder à des zones non définies. Les cellules walkables
 * doivent être entourées uniquement de murs ('1') ou d'autres cellules
 * walkables, jamais d'espaces qui représentent le vide.
 *
 * Caractères walkables vérifiés :
 * - '0' : sol vide  - 'N'/'S'/'E'/'W' : orientations joueur
 * - 'O' : élément spécial  - 'X' : NPC  - 'D' : porte
 */
static bool	check_inside(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 1;
		while (j < map->width - 1)
		{
			if (map->grid[i][j] == '0' || map->grid[i][j] == 'N'
				|| map->grid[i][j] == 'S' || map->grid[i][j] == 'O'
				|| map->grid[i][j] == 'X'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'D')
			{
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
					|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

bool	is_valid_map(t_map *map)
{
	if (!check_borders(map))
		return (false);
	if (!check_sides(map))
		return (false);
	if (!check_inside(map))
		return (false);
	return (true);
}
