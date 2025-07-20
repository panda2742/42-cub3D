/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:18:02 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static void	_static_config(t_render *render);
static void	_load_data(t_render *render, size_t i);
static void	_load_fdata(t_render *render, size_t i);

void	load_sprite(t_render *render)
{
	size_t	i;

	_static_config(render);
	i = -1;
	while (++i < render->sprite.frames)
		render->sprite.data[i].ptr = NULL;
	i = -1;
	while (++i < render->sprite.frames)
		render->sprite.fdata[i].addr = NULL;
	i = -1;
	while (++i < render->sprite.frames)
	{
		_load_data(render, i);
		_load_fdata(render, i);
	}
	if (gettimeofday(&render->sprite.last, NULL) == -1)
	{
		puterr("Error when loading sprite animation frames (time)", false,
			false);
		quit(render);
	}
}

static void	_static_config(t_render *render)
{
	render->sprite.frames = 10;
	render->sprite.current = 0;
	render->sprite.pos.x = -50;
	render->sprite.pos.y = -80;
	render->sprite.interval = 200;
	render->sprite.data = malloc(sizeof(t_img) * render->sprite.frames);
	if (render->sprite.data == NULL)
	{
		puterr("Error when loading sprite animation frames", false, false);
		quit(render);
	}
	render->sprite.fdata = malloc(sizeof(t_frame) * render->sprite.frames);
	if (render->sprite.fdata == NULL)
	{
		puterr("Error when loading sprite animation frames", false, false);
		quit(render);
	}
}

static void	_load_data(t_render *render, size_t i)
{
	char	*name;

	name = ft_sprintf("assets/sprites/samurai%d.xpm", i + 1);
	if (name == NULL)
	{
		puterr("Error when loading sprite animation frames (name)", false,
			false);
		quit(render);
	}
	render->sprite.data[i].ptr = mlx_xpm_file_to_image(render->mlx, name,
			&render->sprite.data[i].width, &render->sprite.data[i].height);
	free(name);
	if (render->sprite.data[i].ptr == NULL)
	{
		puterr("Error when loading sprite animation frames (img data)",
			false, false);
		quit(render);
	}
}

static void	_load_fdata(t_render *render, size_t i)
{
	render->sprite.fdata[i].addr = mlx_get_data_addr(
			render->sprite.data[i].ptr,
			&render->sprite.fdata[i].bits_per_pixel,
			&render->sprite.fdata[i].line_length,
			&render->sprite.fdata[i].endian);
	if (render->sprite.fdata[i].addr == NULL)
	{
		puterr("Error when loading sprite animation frames (frame data)",
			false, false);
		quit(render);
	}
}
