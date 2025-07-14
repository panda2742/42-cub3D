/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/14 17:51:29 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int	_init_render_ctx(t_render *render);

void	render_map(void)
{
	t_render	render;

	_init_render_ctx(&render);
	for (int i = 1; i < 5; i++)
	{
		char	*name = ft_sprintf("assets/textures/wall%d.xpm", i);
		render.textures[i - 1].ptr = mlx_xpm_file_to_image(render.mlx, name, &render.textures[0].width, &render.textures[0].height);
		free(name);
	}
	mlx_hook(render.mlx_win, 2, 1L << 0, key_hook, &render);
	mlx_hook(render.mlx_win, 17, 1L << 0, destroy_hook, &render);
	mlx_loop(render.mlx);
}

static int	_init_render_ctx(t_render *render)
{
	render->mlx = mlx_init();
	if (render->mlx == NULL)
	{
		puterr("MiniLibX initialization failed.", false, false);
		quit(render);
	}
	render->mlx_win = mlx_new_window(
		render->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (render->mlx_win == NULL)
	{
		puterr("MiniLibX window initialization failed.", false, false);
		quit(render);
	}
	render->frame.img = NULL;
	render->frame.addr = NULL;
	gettimeofday(&render->t, NULL);
	render->game.pos = vec2(1.5, 1.5);
	render->game.dir = 0;

	// DEBUG
	render->game.map.width = 10;
	render->game.map.height = 10;
	render->game.map.data = ft_split(
		"1111111111\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1111111111", '\n');

	return (0);
}
