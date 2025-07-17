/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:19:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/17 13:57:50 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_move_player(t_gdata *game, t_direction dir);
static void	_try_move(t_gdata *game, t_vec2 new);

int	key_hook(int keycode, t_render *render)
{
	if (keycode == KEY_ESCAPE)
		quit(render);
	if (keycode == KEY_CAMERA_RIGHT)
	{
		render->game.dir += SENSITIVITY;
		if (render->game.dir > (2 * PI))
			render->game.dir -= (2 * PI);
	}
	if (keycode == KEY_CAMERA_LEFT)
	{
		render->game.dir -= SENSITIVITY;
		if (render->game.dir < 0)
			render->game.dir += (2 * PI);
	}
	if (keycode == KEY_FORWARD)
		_move_player(&render->game, FORWARD);
	if (keycode == KEY_BACKWARD)
		_move_player(&render->game, BACKWARD);
	if (keycode == KEY_LEFT)
		_move_player(&render->game, LEFT);
	if (keycode == KEY_RIGHT)
		_move_player(&render->game, RIGHT);
	return (0);
}

static void	_move_player(t_gdata *game, t_direction dir)
{
	t_vec2	new;

	new.x = game->pos.x;
	new.y = game->pos.y;
	if (dir == FORWARD)
	{
		new.x += cos(game->dir) * VELOCITY;
		new.y += sin(game->dir) * VELOCITY;
	}
	else if (dir == BACKWARD)
	{
		new.x += -cos(game->dir) * VELOCITY;
		new.y += -sin(game->dir) * VELOCITY;
	}
	else if (dir == RIGHT)
	{
		new.x += -sin(game->dir) * VELOCITY;
		new.y += cos(game->dir) * VELOCITY;
	}
	else
	{
		new.x += sin(game->dir) * VELOCITY;
		new.y += -cos(game->dir) * VELOCITY;
	}
	_try_move(game, new);
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
