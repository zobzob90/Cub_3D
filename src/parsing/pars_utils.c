/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:16:35 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/04 12:59:13 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Fonction pour lire le fichier de la map*/

char	**read_files(char *path)
{
	int		fd;
	char	*line;
	char	**lines;
	char	*content;

	content = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	line = get_next_line(fd);
	while (line)
	{
		content = ft_strjoin_free(content, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!content || *content == '\0')
		return (NULL);
	lines = ft_split(content, '\n');
	free(content);
	return (lines);
}

/*Retourne true ou false si la ligne est une texture*/
bool	is_texture(const char *line)
{
	if (!line)
		return (false);
	while (line == ' ' || line == '\t')
		line++;
	if (!ft_strncmp(line, "NO", 3) || !ft_strncmp(line, "SO", 3)
		|| !ft_strncmp(line, "EA", 3) || ft_strncmp(line, "WE", 3))
		return (true);
	return (false);
}

/*Retourne true ou false si la ligne est une couleur*/
bool	is_color(const char *line)
{
	if (!line)
		return (false);
	while (line == ' ' || line == '\t')
		line++;
	if (line == 'F' && (*line + 1) == ' ')
		return (true);
	if (line == 'C' && (*line + 1) == ' ')
		return (true);
	return (false);
}

/*Retourne si il s'agit bien d'une map valide*/
bool	is_map(const char *line)
{
	if (!line)
		return (false);
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ' && *line != 'D' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
