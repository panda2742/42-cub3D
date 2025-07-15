/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 16:26:39 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	loop_hook(t_render *render)
{
	t_time	t1;
	t_time	t2;
	double	fps;
	int		res;
	
	res = gettimeofday(&t1, NULL);
	draw_frame(render);
	res += gettimeofday(&t2, NULL);
	if (res < 0)
		fps = INFINITY;
	fps = 1000000 / ((t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec));
	fprintf(stderr, "\033[2J\033[H%s~%f fps%s\n", C_CRIMSON, fps, RESET);
	return (0);
}
