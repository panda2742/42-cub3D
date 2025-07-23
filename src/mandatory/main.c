/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:18:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/23 16:54:21 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse_cub_file.h"
#include "raycasting.h"

void	launch(t_render *render, t_data *data)
{
	render->game.map.data = data->map.grid;
	render->game.map.height = data->map.height;
	render->game.map.c_color = data->colors.ceil[0]
		<< 16 | data->colors.ceil[1]
		<< 8 | data->colors.floor[2];
	render->game.map.f_color = data->colors.floor[0]
		<< 16 | data->colors.floor[1]
		<< 8 | data->colors.floor[2];
	render->textures[FACE_NORTH].filename
		= ft_strdup(data->textures.north);
	render->textures[FACE_SOUTH].filename
		= ft_strdup(data->textures.south);
	render->textures[FACE_EAST].filename
		= ft_strdup(data->textures.east);
	render->textures[FACE_WEST].filename
		= ft_strdup(data->textures.west);
	render->game.pos.x = data->map.spawn_position[0];
	render->game.pos.y = data->map.spawn_position[1];
	render->game.orientation = data->map.spawn_orientation;
	free_data(data);
	render_map(render);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			exit_code;
	t_render	render;

	ft_bzero(&data, sizeof(t_data));
	(void)ac;
	(void)av;
	if (ac != 2)
	{
		printf("Usage : ./cub3D <*.cub>");
		return (1);
	}
	exit_code = parse_cub_file(av[1], &data);
	if (exit_code != 0)
	{
		if (data.map.grid)
			free_array(data.map.grid);
		return (exit_code);
	}
	launch(&render, &data);
	return (0);
}
