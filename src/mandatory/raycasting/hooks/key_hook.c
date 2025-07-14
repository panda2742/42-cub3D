/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:19:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/14 16:40:20 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_do_move(t_render *render, t_direction dir);

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
		_do_move(render, FORWARD);
	if (keycode == KEY_BACKWARD)
		_do_move(render, BACKWARD);
	if (keycode == KEY_LEFT)
		_do_move(render, LEFT);
	if (keycode == KEY_RIGHT)
		_do_move(render, RIGHT);
	draw_frame(render);
	return (0);
}

static void	_do_move(t_render *render, t_direction dir)
{
	t_vec2	new;
	char	tile;

	new = move_player(&render->game, dir);
	if (new.x < 0 || new.x >= render->game.map.width)
		return ;
	if (new.y < 0 || new.y >= render->game.map.height)
		return ;
	tile = pos_tile(&render->game);
	if (tile != '0')
		return ;
	pos_update(&render->game, new);
}
