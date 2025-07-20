/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:18:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/19 15:56:16 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse_cub_file.h"
#include "raycasting.h"

int	print_cub_data(t_data *data)
{
	int	i;

	i = 0;
	printf("-- Textures --\n");
	printf("north : %s\n", data->textures.north);
	printf("south : %s\n", data->textures.south);
	printf("east : %s\n", data->textures.east);
	printf("west : %s\n", data->textures.west);
	printf("-- Colors --\n");
	printf("ceil : %d %d %d\n", data->colors.ceil[0], data->colors.ceil[1],
		data->colors.ceil[2]);
	printf("floor : %d %d %d\n", data->colors.floor[0], data->colors.floor[1],
		data->colors.floor[2]);
	printf("-- Map infos --\n");
	printf("height : %d\n", data->map.height);
	printf("spawn_position x : %f\n", data->map.spawn_position[0]);
	printf("spawn_position y : %f\n", data->map.spawn_position[1]);
	printf("spawn_orientation : %c\n", data->map.spawn_orientation);
	printf("-- MAP --\n");
	while (data->map.grid[i])
	{
		printf("%s", data->map.grid[i]);
		i++;
	}
	return (0);
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
		return (exit_code);
	printf("This is what cub3D is all about.\n");
	free_data(&data);
	render_map(&render);
	return (0);
}
