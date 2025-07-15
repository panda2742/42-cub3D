/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:05:23 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:57:23 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	puterr(char *errstr, uint8_t require_puterr, uint8_t heaped_str)
{
	char	*str;

	write(2, C_CRIMSON, 18);
	write(2, "cub3D: ", 7);
	if (errstr)
		str = errstr;
	else
		str = "an error occured";
	if (require_puterr)
		perror(str);
	else
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	if (heaped_str && errstr)
		free(errstr);
	write(2, C_RESET, 5);
}
