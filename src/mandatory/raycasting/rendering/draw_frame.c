/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:10:33 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/16 15:01:37 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_frame(t_render *render)
{
	t_rayctx	ctx;
	int			x;
	int			y;

	_init_ctx(render, &ctx);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		dda_algorithm(render, &ctx, x);
		y = 0;
		while (y < ctx.draw_start)
			_put_pixel_on_frame(ctx.frame_addr, x, y++, ctx.c_color);
		_draw_wall(&ctx, x, &y);
		while (y < SCREEN_HEIGHT)
			_put_pixel_on_frame(ctx.frame_addr, x, y++, ctx.f_color);
		x++;
	}
	mlx_put_image_to_window(render->mlx, render->mlx_win, render->frame.img,
		0, 0);
}

static __attribute__((always_inline))
inline void	_put_pixel_on_frame(int *addr, int x, int y, int rgba)
{
	addr[x + (SCREEN_WIDTH * y)] = rgba;
}

static __attribute__((always_inline))
inline void	_init_ctx(t_render *render, t_rayctx *ctx)
{
	ctx->w = (double)SCREEN_WIDTH;
	ctx->h = (double)SCREEN_HEIGHT;
	ctx->dir.x = cos(render->game.dir);
	ctx->dir.y = sin(render->game.dir);
	ctx->plane.x = -ctx->dir.y * FOV_FACTOR;
	ctx->plane.y = ctx->dir.x * FOV_FACTOR;
	ctx->frame_addr = (int *)render->frame.addr;
	ctx->map_def.x = (int)render->game.pos.x;
	ctx->map_def.y = (int)render->game.pos.y;
	ctx->pos.x = render->game.pos.x;
	ctx->pos.y = render->game.pos.y;
	ctx->c_color = render->game.map.c_color;
	ctx->f_color = render->game.map.f_color;
}

static __attribute__((always_inline))
inline void	_draw_wall(t_rayctx *ctx, int x, int *y)
{
	while (y < ctx->draw_end)
	{
		if (ctx->face)
			_put_pixel_on_frame(ctx->frame_addr, x, y, 0);
		else
			_put_pixel_on_frame(ctx->frame_addr, x, y, 0);
		y++;
	}
}
