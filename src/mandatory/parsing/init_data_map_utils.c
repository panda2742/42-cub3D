/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:24:14 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/23 16:50:30 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/parse_cub_file.h"

static int	is_a_valid_char(t_data *data, char c, t_bool *player)
{
	if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'W'
		&& c != 'S')
		return (INVALID_CONFIG);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*player == true)
			return (INVALID_CONFIG);
		*player = true;
		data->map.spawn_orientation = c;
	}
	return (0);
}

static int	is_valid_map_line(t_data *data, t_bool *player, int i, int j)
{
	if (is_a_valid_char(data, data->map.grid[i][j], player) < 0)
		return (INVALID_CONFIG);
	if (*player == true && data->map.spawn_position[0] == -1)
	{
		data->map.spawn_position[0] = j + 0.5;
		data->map.spawn_position[1] = i + 0.5;
	}
	return (0);
}

/* for each char of each line :
 * if it's not ' ' 0 1 NSEW : INVALID_CONFIG
 * if we find two players : INVALID_CONFIG
 * */
int	is_valid_map_format(t_data *data, t_bool *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->map.spawn_position[0] = -1;
	while (data->map.grid[i])
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			if (data->map.grid[i][j] == '\n')
				break ;
			if (is_valid_map_line(data, player, i, j) < 0)
				return (INVALID_CONFIG);
			j++;
		}
		i++;
	}
	if (*player == false)
		return (INVALID_CONFIG);
	return (0);
}
