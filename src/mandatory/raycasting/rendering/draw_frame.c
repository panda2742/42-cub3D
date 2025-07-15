/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:10:33 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 10:00:00 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_emit_rays(t_render *render);

void	draw_frame(t_render *render)
{
	if (render->frame.img != NULL)
	{
		mlx_destroy_image(render->mlx, render->frame.img);
		render->frame.img = NULL;
	}
	render->frame.img = NULL;
	render->frame.img = mlx_new_image(render->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (render->frame.img == NULL)
	{
		puterr("Frame failed to generate (MLX error).", false, false);
		quit(render);
	}
	render->frame.addr = mlx_get_data_addr(
			render->frame.img,
			&render->frame.bits_per_pixel,
			&render->frame.line_length,
			&render->frame.endian
			);
	if (render->frame.addr == NULL)
	{
		puterr("Frame address data failed to get (MLX error).", false, false);
		quit(render);
	}
	_emit_rays(render);
}

static void	_emit_rays(t_render *render)
{
	const t_vec2	dir_vec = vec2(
			cos(render->game.dir), sin(render->game.dir));
	const t_vec2	plane_vec = vec2(
			-dir_vec.y * FOV_FACTOR, dir_vec.x * FOV_FACTOR);

	(void)dir_vec;
	(void)plane_vec;
}
