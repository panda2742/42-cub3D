/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/16 14:52:11 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	loop_hook(t_render *render)
{
	t_time		ts[2];
	int			res;
	long long	t;
	long long	fps;

	res = gettimeofday(&ts[0], NULL);
	draw_frame(render);
	res += gettimeofday(&ts[1], NULL);
	if (res < 0)
		return (0);
	t = (ts[1].tv_sec - ts[0].tv_sec) * 1000000L
		+ (ts[1].tv_usec - ts[0].tv_usec);
	fps = 1000000L / t;
	fprintf(stderr, "\033[2J\033[H%sframe gen. time: %lldμs\t~%lld fps%s\n",
		C_CRIMSON, t, fps, RESET);
	return (0);
}
