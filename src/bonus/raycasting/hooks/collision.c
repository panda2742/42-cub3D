/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:33:30 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/17 13:59:09 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static char	_is_wall(t_gdata *game, double x, double y);

char	check_collision(t_gdata *game, t_vec2 new)
{
	const t_vec2	hitbox_min = {
		.x = new.x - HITBOX_HALFSIZE, .y = new.y - HITBOX_HALFSIZE
	};
	const t_vec2	hitbox_max = {
		.x = new.x + HITBOX_HALFSIZE, .y = new.y + HITBOX_HALFSIZE
	};
	const t_ivec2	start_cell = {
		.x = (int)floor(hitbox_min.x), .y = (int)floor(hitbox_min.y)
	};
	const t_ivec2	end_cell = {
		.x = (int)floor(hitbox_max.x), .y = (int)floor(hitbox_max.y)
	};
	int				i[2];

	i[0] = start_cell.y - 1;
	while (++i[0] <= end_cell.y)
	{
		i[1] = start_cell.x - 1;
		while (++i[1] <= end_cell.x)
		{
			if (_is_wall(game, i[1], i[0]))
				return (1);
		}
	}
	return (0);
}

static char	_is_wall(t_gdata *game, double x, double y)
{
	t_ivec2	map;

	map.x = (int)x;
	map.y = (int)y;
	if (map.x < 0 || map.y < 0
		|| map.y >= game->map.height
		|| map.x >= (int)game->map.lengths[map.y])
		return (1);
	return (game->map.data[map.y][map.x] == '1');
}
