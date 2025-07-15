/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:18:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/04 18:58:44 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/cub3D.h"
#include "../../include/mandatory/parse_cub_file.h"

int print_cub_data(t_data *data)
{
	int i;

	i = 0;
	printf("-- Textures --\n");
	printf("north : %s\n", data->textures.north);
	printf("south : %s\n", data->textures.south);
	printf("east : %s\n", data->textures.east);
	printf("west : %s\n", data->textures.west);
	printf("-- Colors --\n");
	printf("ceil : %d %d %d\n", data->colors.ceil[0], data->colors.ceil[1], data->colors.ceil[2]);
	printf("floor : %d %d %d\n", data->colors.floor[0], data->colors.floor[1], data->colors.floor[2]);
	printf("-- MAP \n");
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data data;

	if (ac != 2)
	{
		printf("Usage : ./cub3D <*.cub>");
		return (1);
	}
	if (parse_cub_file(av[1], &data))
		return (2);
	print_cub_data(&data);
	printf("This is what cub3D is all about.\n");
	free_data(&data);
	return (0);
}
