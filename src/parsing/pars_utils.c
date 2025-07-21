/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:16:35 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 16:47:26 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*Retourne true ou false si la ligne est une texture*/
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

/*Retourne true ou false si la ligne est une couleur*/
bool	is_color(const char *line)
{
	if (!line)
		return (false);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == 'F' && *(line + 1) == ' ')
		return (true);
	if (*line == 'C' && *(line + 1) == ' ')
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
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W'
			&& *line != ' ' && *line != 'D' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
