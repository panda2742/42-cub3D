/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:18:11 by ehosta            #+#    #+#             */
/*   Updated: 2025/06/20 14:42:55 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int	i;

	printf("argc: %d - argv: ", argc);
	i = -1;
	while (++i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(", ");
	}
	printf("\n\nHello World!\n");
	return (0);
}
