/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:08:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/24 11:57:24 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void			_try_move(t_gdata *game, t_vec2 new);
static inline void		_normalize_vector(t_gdata *game, t_vec2 new)
					__attribute__((always_inline));

void	move_player(t_gdata *game, char pressed[6])
{
	t_vec2	new;

	new.x = 0;
	new.y = 0;
	if (pressed[INDEX_FORWARD] && !pressed[INDEX_BACKWARD])
	{
		new.x += cos(game->dir) * VELOCITY;
		new.y += sin(game->dir) * VELOCITY;
	}
	if (pressed[INDEX_BACKWARD] && !pressed[INDEX_FORWARD])
	{
		new.x += -cos(game->dir) * VELOCITY;
		new.y += -sin(game->dir) * VELOCITY;
	}
	if (pressed[INDEX_RIGHT] && !pressed[INDEX_LEFT])
	{
		new.x += -sin(game->dir) * VELOCITY;
		new.y += cos(game->dir) * VELOCITY;
	}
	if (pressed[INDEX_LEFT] && !pressed[INDEX_RIGHT])
	{
		new.x += sin(game->dir) * VELOCITY;
		new.y += -cos(game->dir) * VELOCITY;
	}
	_normalize_vector(game, new);
}

static void	_try_move(t_gdata *game, t_vec2 new)
{
	char	res;

	res = check_collision(game, (t_vec2){.x = new.x, .y = game->pos.y});
	if (!res)
		game->pos.x = new.x;
	res = check_collision(game, (t_vec2){.x = game->pos.x, .y = new.y});
	if (!res)
		game->pos.y = new.y;
}

static __attribute__((always_inline))
inline void	_normalize_vector(t_gdata *game, t_vec2 new)
{
	double	magnitude;

	if (new.x != 0 || new.y != 0)
	{
		magnitude = sqrt(new.x * new.x + new.y * new.y);
		if (magnitude != 0)
		{
			new.x = (new.x / magnitude) * VELOCITY;
			new.y = (new.y / magnitude) * VELOCITY;
		}
	}
	new.x += game->pos.x;
	new.y += game->pos.y;
	_try_move(game, new);
}
