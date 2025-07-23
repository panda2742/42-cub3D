/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/23 16:22:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_init_textures(t_render *render);
static void	_init_render_ctx(t_render *render);
static void	_init_player(t_render *render);
static void	_init_mlx(t_render *render);

void	render_map(t_render *render)
{
	_init_render_ctx(render);
	_init_textures(render);
	mlx_hook(render->mlx_win, 2, 1L << 0, keydown_hook, render);
	mlx_hook(render->mlx_win, 3, 1L << 1, keyup_hook, render);
	mlx_hook(render->mlx_win, 10, 1L << 21, focusout_hook, render);
	mlx_hook(render->mlx_win, 17, 1L << 0, destroy_hook, render);
	mlx_loop_hook(render->mlx, loop_hook, render);
	mlx_loop(render->mlx);
}

static void	_init_textures(t_render *render)
{
	size_t		i;
	t_img		*txtr;

	i = 0;
	while (i < 4)
		render->textures[i++].ptr = NULL;
	i = 0;
	while (i < 4)
	{
		txtr = &render->textures[i++];
		txtr->filename[ft_strlen(txtr->filename) - 1] = 0;
		txtr->ptr = mlx_xpm_file_to_image(
				render->mlx, txtr->filename, &txtr->width, &txtr->height);
		if (txtr->ptr == NULL)
		{
			puterr("Texture creation failed (MLX error).", false, false);
			quit(render);
		}
	}
}

static void	_init_render_ctx(t_render *render)
{
	_init_player(render);
	_init_mlx(render);
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
	mlx_do_key_autorepeatoff(render->mlx);
}

static void	_init_mlx(t_render *render)
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
	if (gettimeofday(&render->keys.last_move, NULL) == -1
		|| gettimeofday(&render->keys.last_rotate, NULL) == -1)
	{
		puterr("Time of day could not be initialized.", false, false);
		quit(render);
	}
}

static void	_init_player(t_render *render)
{
	int	i;

	if (render->game.orientation == 'N')
		render->game.dir = 3 * PI / 2;
	else if (render->game.orientation == 'S')
		render->game.dir = PI / 2;
	else if (render->game.orientation == 'E')
		render->game.dir = PI;
	else if (render->game.orientation == 'W')
		render->game.dir = 0;
	render->game.map.lengths = malloc(sizeof(size_t) * render->game.map.height);
	if (render->game.map.lengths == NULL)
	{
		puterr("Map generation failed (malloc error).", false, false);
		quit(render);
	}
	i = 0;
	while (i < render->game.map.height)
	{
		render->game.map.lengths[i] = ft_strlen(render->game.map.data[i]);
		i++;
	}
	i = -1;
	while (++i < 6)
		render->keys.pressed[i] = 0;
}
