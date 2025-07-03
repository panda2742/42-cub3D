/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:11:03 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 12:37:31 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <ctype.h>
# include <fcntl.h>
# include <inttypes.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_errors_container
{
	uint64_t	cannot_open : 1;
	uint64_t	cannot_read : 1;
	uint64_t	malloc_err : 1;
}	t_errors_container;

typedef union u_parsing_result
{
	uint64_t			val;
	t_errors_container	flags;
}	t_parsing_result;

t_parsing_result	parse_map(const char* map_filename);
int					open_file(const char* filename, t_errors_container* errc);
char*				clean_getline(
						int fd, const char* ign_set, t_errors_container* errc);

#endif