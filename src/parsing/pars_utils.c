/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:16:35 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * read_file_content - Lit l'intégralité d'un fichier et le stocke en mémoire
 * @fd: Descripteur de fichier ouvert en lecture
 *
 * Return: Chaîne contenant tout le contenu du fichier, ou NULL en cas d'erreur
 *
 * Cette fonction auxiliaire lit ligne par ligne un fichier ouvert et
 * concatène toutes les lignes en une seule chaîne de caractères.
 * Elle utilise get_next_line() pour lire chaque ligne et ft_strjoin_free()
 * pour les concaténer efficacement en libérant la mémoire intermédiaire.
 * La première ligne est dupliquée avec ft_strdup(), puis chaque ligne
 * suivante est ajoutée à la chaîne résultante. La fonction continue
 * jusqu'à ce que get_next_line() retourne NULL (fin de fichier).
 */
static char	*read_file_content(int fd)
{
	char	*line;
	char	*content;

	content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!content)
		{
			content = ft_strdup(line);
			free(line);
		}
		else
			content = ft_strjoin_free(content, line);
		line = get_next_line(fd);
	}
	return (content);
}

/**
 * read_files - Lit un fichier et retourne son contenu sous forme de tableau
 * @path: Chemin vers le fichier à lire
 *
 * Return: Tableau de chaînes (une par ligne), ou NULL en cas d'erreur
 *
 * Cette fonction principale lit complètement un fichier et le transforme
 * en tableau de chaînes de caractères, chaque élément correspondant à
 * une ligne du fichier. Processus :
 * 1. Ouvre le fichier en lecture seule avec open()
 * 2. Lit tout le contenu avec read_file_content()
 * 3. Ferme le descripteur de fichier
 * 4. Vérifie que le contenu n'est pas vide
 * 5. Divise le contenu en lignes avec ft_split() sur '\n'
 * 6. Libère le contenu temporaire et retourne le tableau
 * Retourne NULL et affiche une erreur si l'ouverture échoue ou si
 * le fichier est vide.
 */
char	**read_files(char *path)
{
	int		fd;
	char	**lines;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	content = read_file_content(fd);
	close(fd);
	if (!content || *content == '\0')
		return (NULL);
	lines = ft_split(content, '\n');
	return (free(content), lines);
}

/**
 * is_texture - Détermine si une ligne contient une définition de texture
 * @line: Ligne du fichier .cub à analyser
 *
 * Return: true si la ligne définit une texture, false sinon
 *
 * Cette fonction identifie les lignes de configuration de texture dans
 * le fichier .cub. Les textures valides sont :
 * - NO (North/Nord) : texture du mur nord
 * - SO (South/Sud) : texture du mur sud  
 * - EA (East/Est) : texture du mur est
 * - WE (West/Ouest) : texture du mur ouest
 *
 * La fonction ignore les espaces et tabulations en début de ligne,
 * puis vérifie si les deux premiers caractères correspondent à un
 * identifiant de texture valide, suivi d'un espace ou d'une tabulation.
 * Retourne false si la ligne est NULL ou ne correspond à aucun pattern.
 */
bool	is_texture(const char *line)
{
	if (!line)
		return (false);
	while (*line == ' ' || *line == '\t')
		line++;
	if ((!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t')))
		return (true);
	return (false);
}

/**
 * is_color - Détermine si une ligne contient une définition de couleur
 * @line: Ligne du fichier .cub à analyser
 *
 * Return: true si la ligne définit une couleur, false sinon
 *
 * Cette fonction identifie les lignes de configuration de couleur dans
 * le fichier .cub. Les couleurs valides sont :
 * - F : couleur du sol (Floor)
 * - C : couleur du plafond (Ceiling)
 *
 * La fonction ignore les espaces et tabulations en début de ligne,
 * puis vérifie si le premier caractère est 'F' ou 'C' suivi d'un
 * espace ou d'une tabulation. Cette séparation est nécessaire pour
 * distinguer l'identifiant de couleur de sa valeur RGB.
 * Retourne false si la ligne est NULL ou ne correspond pas au format.
 */
bool	is_color(const char *line)
{
	if (!line)
		return (false);
	while (*line == ' ' || *line == '\t')
		line++;
	if ((*line == 'F' || *line == 'C')
		&& (*(line + 1) == ' ' || *(line + 1) == '\t'))
		return (true);
	return (false);
}

/**
 * is_map - Vérifie si une ligne contient des caractères valides pour la carte
 * @line: Ligne du fichier .cub à analyser
 *
 * Return: true si tous les caractères sont valides pour la carte, false sinon
 *
 * Cette fonction valide qu'une ligne ne contient que des caractères
 * autorisés dans la carte du jeu. Les caractères valides sont :
 * - '0' : espace vide (walkable)
 * - '1' : mur  
 * - 'N', 'S', 'E', 'W' : positions et orientations du joueur
 * - 'X' : élément spécial du jeu
 * - 'D' : porte
 * - ' ' : espace vide (non-walkable, pour les bordures)
 * - '\n' : fin de ligne
 *
 * La fonction parcourt chaque caractère de la ligne et retourne false
 * dès qu'un caractère non autorisé est rencontré. Cette validation
 * est essentielle pour s'assurer que la carte ne contient que des
 * éléments que le moteur de jeu peut interpréter correctement.
 */
bool	is_map(const char *line)
{
	if (!line)
		return (false);
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != 'X'
			&& *line != ' ' && *line != 'D' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
