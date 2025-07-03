/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:47:23 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 17:49:50 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void					_read_each_line(int fd, t_map_config* map_config);

t_map_config*	parse_map(const char* map_filename)
{
	int				fd;
	t_map_config*	map_config;

	fd = open(map_filename, O_RDONLY);
	if (fd == -1)
	{
		puterr((char *)map_filename, 1, 0);
		return (NULL);
	}
	map_config = create_map_config();
	if (map_config == NULL)
	{
		if (close(fd) == -1)
			puterr((char *)map_filename, 1, 0);
		puterr("map memory allocation error", 0, 0);
		return (NULL);
	}
	_read_each_line(fd, map_config);
	return (map_config);
}

static void	_read_each_line(int fd, t_map_config* map_config)
{
	char*				line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		free(line);
	}
}
