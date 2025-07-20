/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:02:31 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static unsigned int	_get_color(t_img *data, t_frame *fdata, int x, int y);
static void			_draw_scaled_sprite(t_render *render, t_sprite sprite,
						t_img *data, t_frame *fdata);
static void			_put_pixel(t_render *render, t_ivec2 draw_start,
						unsigned int color);

void	draw_sprite(t_render *render)
{
	t_time		t2;
	long long	t;

	if (gettimeofday(&t2, NULL) == -1)
		return ;
	t = (t2.tv_sec - render->sprite.last.tv_sec) * 1000000L + (t2.tv_usec
			- render->sprite.last.tv_usec);
	if ((t / 1000) > render->sprite.interval)
	{
		render->sprite.current = (render->sprite.current + 1) % 10;
		gettimeofday(&render->sprite.last, NULL);
	}
	_draw_scaled_sprite(render, render->sprite,
		&render->sprite.data[render->sprite.current],
		&render->sprite.fdata[render->sprite.current]);
}

static unsigned int	_get_color(t_img *data, t_frame *fdata, int x, int y)
{
	unsigned int	color;

	if (x < 0 || x > data->width || y < 0 || y > data->height)
		return ((unsigned int)0x0);
	color = *(unsigned int *)(fdata->addr + (y * fdata->line_length)
			+ (x * fdata->bits_per_pixel / 8));
	return (color);
}

static void	_draw_scaled_sprite(t_render *render, t_sprite sprite, t_img *data,
				t_frame *fdata)
{
	t_ivec2			iter;
	unsigned int	color;
	t_ivec2			draw_start;

	iter.y = -1;
	while (++iter.y < data->height)
	{
		iter.x = -1;
		while (++iter.x < data->width)
		{
			color = _get_color(data, fdata, iter.x, iter.y);
			if (color == 4278190080)
				continue ;
			draw_start.x = sprite.pos.x + (iter.x * 3);
			draw_start.y = sprite.pos.y + (iter.y * 3);
			_put_pixel(render, draw_start, color);
		}
	}
}

static void	_put_pixel(t_render *render, t_ivec2 draw_start,
				unsigned int color)
{
	int		i;
	int		j;
	t_ivec2	dest_pixel;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			dest_pixel.x = draw_start.x + j;
			dest_pixel.y = draw_start.y + i;
			if (dest_pixel.x >= 0 && dest_pixel.x < SCREEN_WIDTH
				&& dest_pixel.y >= 0 && dest_pixel.y < SCREEN_HEIGHT)
			{
				*(unsigned int *)(render->frame.addr
						+ (dest_pixel.y * render->frame.line_length)
						+ (dest_pixel.x * (render->frame.bits_per_pixel / 8)))
					= color;
			}
		}
	}
}
