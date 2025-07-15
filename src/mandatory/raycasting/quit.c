/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:34:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:54:19 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_free_textures(t_render *render);

void	quit(t_render *render)
{
	if (render->game.map.data)
	{
		ft_free_strtab(render->game.map.data);
		render->game.map.data = NULL;
	}
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
}
