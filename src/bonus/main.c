/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:18:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 13:18:07 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycasting_bonus.h"
#include "parse_cub_file.h"

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
	printf("-- MAP --\n");
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		exit_code;

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
	print_cub_data(&data);
	printf("This is what cub3D is all about.\n");
	// free_data(&data);
	t_render	render;

	render.game.map.data = data.map;
	render.game.map.height = 14;
	render.game.map.c_color = data.colors.ceil[0] << 16 | data.colors.ceil[1] << 8 | data.colors.floor[2];
	render.game.map.f_color = data.colors.floor[0] << 16 | data.colors.floor[1] << 8 | data.colors.floor[2];
	render.textures[FACE_NORTH].filename
		= ft_strdup(data.textures.north);
	render.textures[FACE_SOUTH].filename
		= ft_strdup(data.textures.south);
	render.textures[FACE_EAST].filename
		= ft_strdup(data.textures.east);
	render.textures[FACE_WEST].filename
		= ft_strdup(data.textures.west);
	render_map(&render);
	return (0);
}
