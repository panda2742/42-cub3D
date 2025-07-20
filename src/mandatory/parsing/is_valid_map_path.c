/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:23:48 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/19 15:23:50 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/parse_cub_file.h"

static int	get_file_size(char *config_file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(config_file, O_RDONLY);
	if (fd < 0)
		return (OPEN_ERROR);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

static int	free_file_content(char **content, int i)
{
	while (--i >= 0)
		free(content[i]);
	free(content);
	return (MALLOC_ERROR);
}

static int	read_and_store_lines(char **content, int fd, int size)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		content[i] = ft_strdup(line);
		free(line);
		if (!content[i])
			return (free_file_content(content, i));
		i++;
		line = get_next_line(fd);
	}
	if (i != size)
		return (free_file_content(content, i));
	content[i] = NULL;
	return (0);
}

static int	get_file_content(char ***file_content, int fd, int size)
{
	*file_content = malloc(sizeof(char *) * (size + 1));
	if (!*file_content)
		return (MALLOC_ERROR);
	return (read_and_store_lines(*file_content, fd, size));
}

int	is_valid_map_path(char *map, char ***file_content)
{
	int	size;
	int	fd;
	int	exit_code;

	if (ft_strncmp(map + ft_strlen(map) - 4, ".cub", 5))
		return (INVALID_CONFIG);
	size = get_file_size(map);
	if (size == 0)
		return (FILE_EMPTY);
	if (size < 0)
		return (size);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (OPEN_ERROR);
	exit_code = get_file_content(file_content, fd, size);
	close(fd);
	return (exit_code);
}
