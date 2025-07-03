/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:11:03 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 17:42:08 by ehosta           ###   ########.fr       */
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
# include "colors.h"
# include "libft.h"

typedef struct	s_map_config
{
	char*	no_texture_name;
	char*	so_texture_name;
	char*	we_texture_name;
	char*	ea_texture_name;
	char*	floor_color;
	char*	ceiling_color;
	char**	lines;
}	t_map_config;

t_map_config*	parse_map(const char* map_filename);
t_map_config*	create_map_config(void);
void			puterr(
					char* errstr,
					uint8_t require_puterr,
					uint8_t heaped_str);
char			*ft_sprintf(const char *format, ...);
size_t			int_size(int n);

#endif