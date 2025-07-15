/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:59:15 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int	_init_render_ctx(t_render *render);
static void	_init_player(t_render *render);

void	render_map(void)
{
	t_render	render;
	t_img		*txtr;
	size_t		i;

	_init_render_ctx(&render);
	i = 0;
	while (i < 4)
		render.textures[i++].ptr = NULL;
	i = 0;
	while (i < 4)
	{
		txtr = &render.textures[i++];
		txtr->ptr = mlx_xpm_file_to_image(
				render.mlx, txtr->filename, &txtr->width, &txtr->height);
		if (txtr->ptr == NULL)
		{
			puterr("Texture creation failed (MLX error).", false, false);
			quit(&render);
		}
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
	_init_player(render);
	// !DEBUG
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
			"1N00000001\n"
			"1111111111", '\n');
	render->textures[0].filename = ft_strdup("assets/textures/wall1.xpm");
	render->textures[1].filename = ft_strdup("assets/textures/wall2.xpm");
	render->textures[2].filename = ft_strdup("assets/textures/wall3.xpm");
	render->textures[3].filename = ft_strdup("assets/textures/wall4.xpm");
	// DEBUG!
	return (0);
}

static void	_init_player(t_render *render)
{
	render->game.pos = vec2(1.5, 1.5);
	render->game.orientation = 'N';
	if (render->game.orientation == 'N')
		render->game.dir = PI / 2;
	else if (render->game.orientation == 'S')
		render->game.dir = 3 * PI / 2;
	else if (render->game.orientation == 'E')
		render->game.dir = PI;
	else if (render->game.orientation == 'W')
		render->game.dir = 2 * PI;
}
