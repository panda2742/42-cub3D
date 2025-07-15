/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:45:41 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:59:24 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

unsigned int	rgba(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return ((1 - a) << 24 | r << 16 | g << 8 | b);
}

void	put_pixel_on_frame(t_frame *img, int x, int y, int rgba)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = rgba;
}
