/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:24 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * is_valid_color - Vérifie si une valeur de couleur est dans la plage valide
 * @value: Valeur entière à vérifier (composante R, G ou B)
 *
 * Return: true si la valeur est entre 0 et 255 inclus, false sinon
 *
 */
static bool	is_valid_color(int value)
{
	return (value >= 0 && value <= 255);
}

/**
 * is_val_numb - Vérifie si une chaîne contient uniquement des chiffres
 * @str: Chaîne de caractères à analyser
 *
 * Return: 1 si la chaîne ne contient que des chiffres, 0 sinon
 *
 * Cette fonction parcourt chaque caractère de la chaîne pour s'assurer
 * qu'il s'agit uniquement de chiffres (0-9). Elle est utilisée pour
 * valider que les composantes de couleur sont des nombres valides avant
 * de les convertir avec ft_atoi(). Retourne 0 si la chaîne est NULL,
 * vide, ou contient des caractères non numériques.
 */
static int	is_val_numb(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * parse_rgb - Parse une chaîne RGB et remplit une structure t_color
 * @str: Chaîne contenant les valeurs RGB séparées par des virgules
 * @color: Pointeur vers la structure t_color à remplir
 *
 * Return: 1 en cas de succès, 0 en cas d'erreur
 *
 * Cette fonction analyse une chaîne au format "R,G,B" et extrait les
 * trois composantes de couleur. Elle effectue plusieurs validations :
 * - Divise la chaîne par les virgules avec ft_split()
 * - Vérifie qu'il y a exactement 3 composantes
 * - Valide que chaque composante ne contient que des chiffres
 * - Convertit chaque composante en entier avec ft_atoi()
 * - Vérifie que chaque valeur est dans la plage 0-255
 * - Remplit la structure t_color avec les valeurs validées
 * Libère automatiquement la mémoire allouée en cas d'erreur.
 */
static int	parse_rgb(char *str, t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (ft_free_tab(rgb), 0);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (ft_free_tab(rgb), 0);
	if (!is_val_numb(rgb[0]) || !is_val_numb(rgb[1]) || !is_val_numb(rgb[2]))
		return (ft_free_tab(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
		return (ft_free_tab(rgb), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (ft_free_tab(rgb), 1);
}

/**
 * assign_color_to_map - Assigne une couleur au sol ou au plafond de la carte
 * @type: Type de couleur ("F" pour floor/sol, "C" pour ceiling/plafond)
 * @color: Structure t_color contenant les valeurs RGB à assigner
 * @map: Pointeur vers la structure de carte où stocker la couleur
 *
 * Return: true en cas de succès, false si erreur ou couleur déjà définie
 *
 * Cette fonction assigne une couleur validée au sol (F) ou au plafond (C)
 * de la carte. Elle vérifie d'abord que la couleur n'a pas déjà été
 * définie (en testant si r != -1) pour éviter les doublons. Si le type
 * est "F", la couleur est assignée à map->floor. Si le type est "C",
 * elle est assignée à map->ceiling. Retourne false si le type n'est
 * pas reconnu ou si la couleur était déjà définie.
 */
static bool	assign_color_to_map(char *type, t_color color, t_map *map)
{
	if (!ft_strncmp(type, "F", 1))
	{
		if (map->floor.r != -1)
			return (false);
		map->floor = color;
	}
	else if (!ft_strncmp(type, "C", 1))
	{
		if (map->ceiling.r != -1)
			return (false);
		map->ceiling = color;
	}
	else
		return (false);
	return (true);
}

/**
 * parse_color - Parse une ligne de configuration de couleur
 * @line: Ligne du fichier .cub contenant une définition de couleur
 * @map: Pointeur vers la structure de carte à modifier
 *
 * Return: true si le parsing réussit, false en cas d'erreur
 *
 * Cette fonction principale parse une ligne de couleur du fichier .cub.
 * Format attendu : "F R,G,B" ou "C R,G,B" où :
 * - F/C indique floor (sol) ou ceiling (plafond)
 * - R,G,B sont les composantes RGB séparées par des virgules
 *
 * Processus :
 * 1. Divise la ligne en tokens par les espaces
 * 2. Vérifie qu'il y a exactement 2 tokens (type et couleur)
 * 3. Parse les valeurs RGB avec parse_rgb()
 * 4. Assigne la couleur à la carte avec assign_color_to_map()
 * 5. Libère la mémoire des tokens
 * Retourne false et libère la mémoire en cas d'erreur à n'importe quelle étape.
 */
bool	parse_color(char *line, t_map *map)
{
	char	**tokens;
	t_color	color;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (ft_free_tab(tokens), false);
	i = 0;
	while (tokens[i])
		i++;
	if (i != 2)
		return (ft_free_tab(tokens), false);
	if (!parse_rgb(tokens[1], &color))
		return (ft_free_tab(tokens), false);
	if (!assign_color_to_map(tokens[0], color, map))
		return (ft_free_tab(tokens), false);
	ft_free_tab(tokens);
	return (true);
}
