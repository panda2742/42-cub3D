/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:19:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/16 13:09:55 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void				_move_player(t_gdata *game, t_direction dir);
static unsigned char	_do_side_move(t_gdata *game,
							t_vec2 new, t_direction dir);
static void				_do_front_move(t_gdata *game, t_vec2 new,
							t_direction dir, unsigned char move_is_possible);

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
	_do_front_move(game, new, dir, _do_side_move(game, new, dir));
}

static unsigned char	_do_side_move(t_gdata *game,
							t_vec2 new, t_direction dir)
{
	if (new.x <= (0.0 + BORDER_MARGIN)
		|| new.x >= (game->map.width - 1 - BORDER_MARGIN))
		return (0);
	if (dir == RIGHT)
	{
		if (game->map.data[(int)new.y][(int)(new.x + BORDER_MARGIN)] == '1')
			return (0);
	}
	else if (dir == LEFT)
	{
		if (game->map.data[(int)new.y][(int)(new.x - BORDER_MARGIN)] == '1')
			return (0);
	}
	game->pos.x = new.x;
	return (1);
}

static void	_do_front_move(t_gdata *game, t_vec2 new, t_direction dir,
				unsigned char move_is_possible)
{
	if (new.y <= (0.0 + BORDER_MARGIN)
		|| new.y >= (game->map.height - 1 - BORDER_MARGIN))
		return ;
	if (dir == FORWARD)
	{
		if (game->map.data[(int)(new.y + BORDER_MARGIN)][(int)new.x] == '1')
			return ;
	}
	else if (dir == BACKWARD)
	{
		if (game->map.data[(int)(new.y - BORDER_MARGIN)][(int)new.x] == '1')
			return ;
	}
	if (move_is_possible)
		game->pos.y = new.y;
}
