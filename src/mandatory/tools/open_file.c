/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:02:15 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 12:11:16 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(const char* filename, t_errors_container* errc)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		errc->cannot_open = 1;
		return (-1);
	}
	errc->cannot_open = 0;
	return (fd);
}
