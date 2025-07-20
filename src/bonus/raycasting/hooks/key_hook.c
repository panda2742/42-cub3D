/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:19:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

int	keydown_hook(int keycode, t_render *render)
{
	if (keycode == KEY_ESCAPE)
		quit(render);
	if (keycode == KEY_FORWARD)
		render->keys.pressed[INDEX_FORWARD] = 1;
	else if (keycode == KEY_LEFT)
		render->keys.pressed[INDEX_LEFT] = 1;
	else if (keycode == KEY_BACKWARD)
		render->keys.pressed[INDEX_BACKWARD] = 1;
	else if (keycode == KEY_RIGHT)
		render->keys.pressed[INDEX_RIGHT] = 1;
	else if (keycode == KEY_CAMERA_LEFT)
		render->keys.pressed[INDEX_CAMERA_LEFT] = 1;
	else if (keycode == KEY_CAMERA_RIGHT)
		render->keys.pressed[INDEX_CAMERA_RIGHT] = 1;
	return (0);
}

int	keyup_hook(int keycode, t_render *render)
{
	if (keycode == KEY_FORWARD)
		render->keys.pressed[INDEX_FORWARD] = 0;
	else if (keycode == KEY_LEFT)
		render->keys.pressed[INDEX_LEFT] = 0;
	else if (keycode == KEY_BACKWARD)
		render->keys.pressed[INDEX_BACKWARD] = 0;
	else if (keycode == KEY_RIGHT)
		render->keys.pressed[INDEX_RIGHT] = 0;
	else if (keycode == KEY_CAMERA_LEFT)
		render->keys.pressed[INDEX_CAMERA_LEFT] = 0;
	else if (keycode == KEY_CAMERA_RIGHT)
		render->keys.pressed[INDEX_CAMERA_RIGHT] = 0;
	return (0);
}
