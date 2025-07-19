/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:43:18 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/18 21:23:46 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_minimap(t_render *render)
{
	render->mini_frame.img = mlx_new_image(render->mlx, MINIMAP_WIDTH,
			MINIMAP_HEIGHT);
	if (render->mini_frame.img == NULL)
	{
		puterr("Minimap frame initialization failed", false, false);
		quit(render);
	}
	render->mini_frame.addr = mlx_get_data_addr(render->mini_frame.img,
			&render->mini_frame.bits_per_pixel,
			&render->mini_frame.line_length,
			&render->mini_frame.endian);
	if (render->mini_frame.addr == NULL)
	{
		puterr("Minimap frame initialization failed", false, false);
		quit(render);
	}
}
