/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:10:26 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 17:21:44 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static void	_draw_sky_view(t_render *render);
static void	_draw_dot(t_render *render);
static void	_put_pixel(t_render *render, t_vec2 cur_map_coord, t_ivec2 iter);
static void	_put_minimap_on_window(t_render *render);

void	draw_minimap(t_render *render)
{
	_draw_sky_view(render);
	_draw_dot(render);
	_put_minimap_on_window(render);
}

static void	_draw_sky_view(t_render *render)
{
	t_vec2	min_map_coord;
	t_vec2	cur_map_coord;
	t_ivec2	iter;

	min_map_coord.x = render->game.pos.x - (MINIMAP_STEP * MINIMAP_WIDTH / 2);
	min_map_coord.y = render->game.pos.y - (MINIMAP_STEP * MINIMAP_WIDTH / 2);
	iter.y = -1;
	while (++iter.y < MINIMAP_WIDTH)
	{
		if (iter.y < 0)
			continue ;
		iter.x = -1;
		while (++iter.x < MINIMAP_WIDTH)
		{
			if (iter.x < 0 || iter.x >= MINIMAP_WIDTH
				|| iter.y >= MINIMAP_WIDTH)
				continue ;
			cur_map_coord.x = min_map_coord.x + (iter.x * MINIMAP_STEP);
			cur_map_coord.y = min_map_coord.y + (iter.y * MINIMAP_STEP);
			_put_pixel(render, cur_map_coord, iter);
		}
	}
}

static void	_put_pixel(t_render *render, t_vec2 cur_map_coord, t_ivec2 iter)
{
	unsigned int	color;
	char			tile;

	color = render->game.map.c_color;
	if (cur_map_coord.x >= 0 && cur_map_coord.y >= 0
		&& cur_map_coord.y < render->game.map.height
		&& cur_map_coord.x
		< render->game.map.lengths[(int)cur_map_coord.y])
	{
		tile = render->game.map.data[(int)cur_map_coord.y]
		[(int)cur_map_coord.x];
		if (tile == '1')
			color = 0x00444444;
		else if (tile == '0')
			color = render->game.map.f_color;
	}
	*(unsigned int *)(render->mini_frame.addr
			+ ((int)iter.y * render->mini_frame.line_length)
			+ ((int)iter.x * render->mini_frame.bits_per_pixel / 8))
		= color;
}

static void	_draw_dot(t_render *render)
{
	int		i;
	int		j;
	t_ivec2	pos;

	j = -1;
	while (++j < 5)
	{
		i = -1;
		while (++i < 5)
		{
			pos.x = MINIMAP_WIDTH / 2 + (i - 2);
			pos.y = MINIMAP_WIDTH / 2 + (j - 2);
			*(unsigned int *)(render->mini_frame.addr
					+ (pos.y * render->mini_frame.line_length)
					+ (pos.x * render->mini_frame.bits_per_pixel / 8))
				= 0x000000FF;
		}
	}
}

static void	_put_minimap_on_window(t_render *render)
{
	t_ivec2	pos;
	t_ivec2	iter;

	pos.y = MINIMAP_Y;
	iter.y = -1;
	while (++iter.y < MINIMAP_WIDTH)
	{
		iter.x = -1;
		pos.x = MINIMAP_X;
		while (++iter.x < MINIMAP_WIDTH)
		{
			if (pos.y < 0 || pos.x < 0 || pos.y > SCREEN_HEIGHT
				|| pos.x > SCREEN_WIDTH || iter.y < 0 || iter.x < 0
				|| iter.y > MINIMAP_WIDTH || iter.x > MINIMAP_WIDTH)
				continue ;
			*(unsigned int *)(render->frame.addr
					+ (pos.y * render->frame.line_length)
					+ (pos.x * render->frame.bits_per_pixel / 8))
				= *(unsigned int *)(render->mini_frame.addr
					+ (iter.y * render->mini_frame.line_length)
					+ (iter.x * render->mini_frame.bits_per_pixel / 8));
			pos.x++;
		}
		pos.y++;
	}
}
