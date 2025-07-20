/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:32:36 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static inline void	_dda_calc_step(t_rayctx *ctx)
					__attribute__((always_inline));
static inline void	_dda_progress(t_render *render, t_rayctx *ctx)
					__attribute__((always_inline));
static inline void	_dda_calc_line_length(t_rayctx *ctx)
					__attribute__((always_inline));
static inline void	_dda_get_wall_x(t_rayctx *ctx)
					__attribute__((always_inline));

char	dda_algorithm(t_render *render, t_rayctx *ctx, int x)
{
	ctx->cam_x = (x << 1) / ctx->w - 1.0;
	ctx->ray_dir.x = ctx->dir.x + ctx->plane.x * ctx->cam_x;
	ctx->ray_dir.y = ctx->dir.y + ctx->plane.y * ctx->cam_x;
	ctx->map.x = ctx->map_def.x;
	ctx->map.y = ctx->map_def.y;
	ctx->delta_dist.x = 1e30;
	ctx->delta_dist.y = 1e30;
	if (ctx->ray_dir.x != 0)
		ctx->delta_dist.x = fabs(1 / ctx->ray_dir.x);
	if (ctx->ray_dir.y != 0)
		ctx->delta_dist.y = fabs(1 / ctx->ray_dir.y);
	_dda_calc_step(ctx);
	_dda_progress(render, ctx);
	_dda_calc_line_length(ctx);
	_dda_get_wall_x(ctx);
	return (1);
}

static __attribute__((always_inline))
inline void	_dda_calc_step(t_rayctx *ctx)
{
	if (ctx->ray_dir.x < 0)
	{
		ctx->step.x = -1;
		ctx->side_dist.x = (ctx->pos.x - ctx->map.x) * ctx->delta_dist.x;
	}
	else
	{
		ctx->step.x = 1;
		ctx->side_dist.x = (ctx->map.x + 1.0 - ctx->pos.x) * ctx->delta_dist.x;
	}
	if (ctx->ray_dir.y < 0)
	{
		ctx->step.y = -1;
		ctx->side_dist.y = (ctx->pos.y - ctx->map.y) * ctx->delta_dist.y;
	}
	else
	{
		ctx->step.y = 1;
		ctx->side_dist.y = (ctx->map.y + 1.0 - ctx->pos.y) * ctx->delta_dist.y;
	}
}

static __attribute__((always_inline))
inline void	_dda_progress(t_render *render, t_rayctx *ctx)
{
	while (1)
	{
		ctx->face = ctx->side_dist.x >= ctx->side_dist.y;
		if (ctx->side_dist.x < ctx->side_dist.y)
		{
			ctx->side_dist.x += ctx->delta_dist.x;
			ctx->map.x += ctx->step.x;
		}
		else
		{
			ctx->side_dist.y += ctx->delta_dist.y;
			ctx->map.y += ctx->step.y;
		}
		if (ctx->map.x < 0 || ctx->map.y < 0
			|| ctx->map.y >= render->game.map.height
			|| ctx->map.x >= (int)render->game.map.lengths[ctx->map.y])
			break ;
		if (render->game.map.data[ctx->map.y][ctx->map.x] == '1')
			break ;
	}
}

static __attribute__((always_inline))
inline void	_dda_calc_line_length(t_rayctx *ctx)
{
	if (ctx->face == FACE_VERTICAL)
		ctx->perp_dist = (ctx->map.x - ctx->pos.x + ((1 - ctx->step.x) / 2))
			/ ctx->ray_dir.x;
	else
		ctx->perp_dist = (ctx->map.y - ctx->pos.y + ((1 - ctx->step.y) / 2))
			/ ctx->ray_dir.y;
	if (ctx->perp_dist < 0.0001 || isnan(ctx->perp_dist)
		|| isinf(ctx->perp_dist))
		return ;
	ctx->line_height = (int)(SCREEN_HEIGHT / ctx->perp_dist);
	ctx->draw_start = -(ctx->line_height >> 1) + (SCREEN_HEIGHT >> 1);
	ctx->draw_end = (ctx->line_height >> 1) + (SCREEN_HEIGHT >> 1);
	if (ctx->draw_end > SCREEN_HEIGHT)
		ctx->draw_end = SCREEN_HEIGHT;
}

static __attribute__((always_inline))
inline void	_dda_get_wall_x(t_rayctx *ctx)
{
	if (ctx->face == FACE_VERTICAL)
	{
		ctx->wall_x = ctx->pos.y + ctx->perp_dist * ctx->ray_dir.y;
		if (ctx->ray_dir.x > 0)
			ctx->texture_index = FACE_EAST;
		else
			ctx->texture_index = FACE_WEST;
	}
	else
	{
		ctx->wall_x = ctx->pos.x + ctx->perp_dist * ctx->ray_dir.x;
		if (ctx->ray_dir.y > 0)
			ctx->texture_index = FACE_NORTH;
		else
			ctx->texture_index = FACE_SOUTH;
	}
	ctx->wall_x -= floor(ctx->wall_x);
}
