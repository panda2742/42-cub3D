/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:29:54 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:57:55 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_vec2	move_player(t_gdata *game, t_direction dir)
{
	t_vec2	new;

	new = vec2(game->pos.x, game->pos.y);
	if (dir == FORWARD)
	{
		new.y += cos(game->dir) * VELOCITY;
		new.x += sin(game->dir) * VELOCITY;
	}
	else if (dir == BACKWARD)
	{
		new.y += -cos(game->dir) * VELOCITY;
		new.x += -sin(game->dir) * VELOCITY;
	}
	else if (dir == RIGHT)
	{
		new.y += -sin(game->dir) * VELOCITY;
		new.x += cos(game->dir) * VELOCITY;
	}
	else
	{
		new.y += sin(game->dir) * VELOCITY;
		new.x += -cos(game->dir) * VELOCITY;
	}
	return (new);
}

void	pos_update(t_gdata *game, t_vec2 new)
{
	game->pos.x = new.x;
	game->pos.y = new.y;
}

char	pos_tile(t_gdata *game)
{
	const size_t	y = game->map.height - 1 - (int)game->pos.y;
	const size_t	x = (int)game->pos.x;

	return (game->map.data[y][x]);
}
