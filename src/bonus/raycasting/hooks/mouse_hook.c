/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:25:24 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 20:20:49 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

int	mousemove_hook(int x, int y, t_render *render)
{
	float	delta;

	(void)y;
	if (render->last_mouse == -1)
		render->last_mouse = x;
	delta = x - render->last_mouse;
	render->last_mouse = x;
	render->game.dir += delta * SENSITIVITY;
	if (render->game.dir > (2 * PI))
		render->game.dir -= (2 * PI);
	if (render->game.dir < 0)
		render->game.dir += (2 * PI);
	if (x <= 10 || x >= (SCREEN_WIDTH - 10))
		mouse_warp(render);
	return (0);
}
