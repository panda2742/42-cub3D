/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:11:03 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 10:00:22 by ehosta           ###   ########.fr       */
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
# include "mlx.h"

void			puterr(
					char *errstr,
					uint8_t require_puterr,
					uint8_t heaped_str);
char			*ft_sprintf(const char *format, ...);
size_t			int_size(int n);

#endif