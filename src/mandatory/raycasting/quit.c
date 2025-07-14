/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:34:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/14 16:57:08 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

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
	mlx_destroy_display(render->mlx);
	free(render->mlx);
	render->mlx = NULL;
	exit(EXIT_SUCCESS);
}
