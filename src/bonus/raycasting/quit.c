/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:34:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static void	_free_textures(t_render *render);
static void	_free_map(t_map *map);
static void	_free_sprite(t_render *render);

void	quit(t_render *render)
{
	_free_map(&render->game.map);
	if (render->mlx == NULL)
		return ;
	if (render->frame.img)
	{
		mlx_destroy_image(render->mlx, render->frame.img);
		render->frame.img = NULL;
	}
	if (render->mlx_win)
	{
		mlx_destroy_window(render->mlx, render->mlx_win);
		render->mlx_win = NULL;
	}
	_free_textures(render);
	mlx_destroy_display(render->mlx);
	free(render->mlx);
	render->mlx = NULL;
	exit(EXIT_SUCCESS);
}

static void	_free_textures(t_render *render)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (render->textures[i].filename)
		{
			free(render->textures[i].filename);
			render->textures[i].filename = NULL;
		}
		if (render->textures[i].ptr)
		{
			mlx_destroy_image(render->mlx, render->textures[i].ptr);
			render->textures[i].ptr = NULL;
		}
		i++;
	}
	_free_sprite(render);
}

static void	_free_map(t_map *map)
{
	if (map->data)
	{
		ft_free_strtab(map->data);
		map->data = NULL;
	}
	if (map->lengths)
	{
		free(map->lengths);
		map->lengths = NULL;
	}
}

static void	_free_sprite(t_render *render)
{
	size_t	i;

	if (render->sprite.data)
	{
		i = -1;
		while (render->sprite.data[++i].ptr && i < render->sprite.frames)
			mlx_destroy_image(render->mlx, render->sprite.data[i].ptr);
		free(render->sprite.data);
		render->sprite.data = NULL;
	}
	if (render->sprite.fdata)
	{
		free(render->sprite.fdata);
		render->sprite.fdata = NULL;
	}
	if (render->mini_frame.img)
	{
		mlx_destroy_image(render->mlx, render->mini_frame.img);
		render->mini_frame.img = NULL;
	}
}
