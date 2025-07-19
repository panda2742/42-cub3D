/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:10:26 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/19 16:11:29 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void			_draw_scaled_minimap(t_render *render);
static void			_put_pixel(t_render *render, t_ivec2 draw_start,
						unsigned int color);

void	draw_minimap(t_render *render)
{
	_draw_scaled_minimap(render);
}

static void	_draw_scaled_minimap(t_render *render)
{
	t_ivec2			iter;
	t_ivec2			draw_start;

	iter.y = -1;
	while (++iter.y < MINIMAP_HEIGHT)
	{
		iter.x = -1;
		while (++iter.x < MINIMAP_WIDTH)
		{
			draw_start.x = iter.x - 20 + SCREEN_WIDTH - MINIMAP_WIDTH;
			draw_start.y = iter.y + 20;
			_put_pixel(render, draw_start, render->game.map.f_color);
		}
	}
}

static void	_put_pixel(t_render *render, t_ivec2 draw_start,
				unsigned int color)
{
	t_ivec2	dest_pixel;

	dest_pixel.x = draw_start.x;
	dest_pixel.y = draw_start.y;
	if (dest_pixel.x >= 0 && dest_pixel.x < SCREEN_WIDTH
		&& dest_pixel.y >= 0 && dest_pixel.y < SCREEN_HEIGHT)
	{
		*(unsigned int *)(render->frame.addr
				+ (dest_pixel.y * render->frame.line_length)
				+ (dest_pixel.x * (render->frame.bits_per_pixel / 8)))
			= color;
	}
}
