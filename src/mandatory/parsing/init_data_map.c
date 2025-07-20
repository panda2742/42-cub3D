/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:24:23 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/19 17:21:01 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/parse_cub_file.h"

static int	get_map_size(char **file_content, int i)
{
	int	j;

	j = i;
	while (file_content[j])
		j++;
	return (j - i);
}

/* if a '0' or the player is
 *  - adjacent to a space, or
 *  - on the edge of the ma :
 * the map can't be surrounded by wall : invalid configuration */
static int	check_wall(char **map, int i, int size)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'D')
		{
			if (i == 0 || i == size || j == 0 || map[i][j + 1] == '\n')
				return (INVALID_CONFIG);
			if ((map[i][j - 1] && map[i][j - 1] == ' ') || (map[i][j + 1]
					&& map[i][j + 1] == ' ') || (map[i - 1][j] && map[i
					- 1][j] == ' ') || (map[i + 1][j] && map[i + 1][j] == ' '))
				return (INVALID_CONFIG);
		}
		j++;
	}
	return (0);
}

/* for each line of the map ... */
static int	are_wall_closed(char **map, int size)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (check_wall(map, i, size))
			return (INVALID_CONFIG);
		i++;
	}
	return (0);
}

int	get_map(t_data *data, char **file_content, int i)
{
	int	j;

	j = 0;
	data->map.grid = malloc(sizeof(char *) * (get_map_size(file_content, i)
				+ 1));
	if (!data->map.grid)
		return (MALLOC_ERROR);
	while (file_content[i])
	{
		data->map.grid[j] = ft_strdup(file_content[i]);
		if (!data->map.grid[j])
		{
			while (j - 1 >= 0)
			{
				free(data->map.grid[j - 1]);
				j--;
			}
			return (MALLOC_ERROR);
		}
		j++;
		i++;
	}
	data->map.grid[j] = NULL;
	return (0);
}

/*
 * We check first if all chars in map are valid (0 1 ' ' or N/S/E/W)
 *    in same time : if there is only one player on the map
 * then if walls are correctly closed
 * */
//
// un check en plus pour savoir si le joueur est bien enferme dans des murs ?
//
int	is_valid_map(t_data *data)
{
	int		size;
	int		exit_code;
	t_bool	player;

	player = false;
	size = 0;
	while (!ft_strncmp(data->map.grid[size], "\n", 2))
		size++;
	size = 0;
	while (data->map.grid[size])
		size++;
	exit_code = is_valid_map_format(data, &player);
	if (exit_code < 0)
		return (INVALID_CONFIG);
	exit_code = are_wall_closed(data->map.grid, size);
	if (exit_code < 0)
		return (INVALID_CONFIG);
	data->map.height = size;
	return (0);
}
