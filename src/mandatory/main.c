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

#include "cub3D.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;
	if (ac != 2)
	{
		printf("Usage : ./cub3D <*.cub>");
		return (1);
	}
	if (parse_cub_file(argv[1], &data))
		return (2);
	print_cub_data(&data);
	printf("This is what cub3D is all about.\n");
	return (0);
}
