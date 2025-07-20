/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 20:16:28 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static void	_print_fps(t_time *t1);
static void	_do_move(t_time *t1, t_render *render);
static void	_check_for_move(long long t, t_render *render);
static void	_check_for_rotate(long long t, t_render *render);

int	loop_hook(t_render *render)
{
	t_time		ts;

	if (gettimeofday(&ts, NULL))
		return (0);
	_do_move(&ts, render);
	draw_frame(render);
	_print_fps(&ts);
	return (0);
}

static void	_print_fps(t_time *t1)
{
	t_time		t2;
	long long	t;

	if (gettimeofday(&t2, NULL))
		return ;
	t = (t2.tv_sec - t1->tv_sec) * 1000000L + (t2.tv_usec - t1->tv_usec);
	fprintf(stderr, "\033[2J\033[H%sframe gen. time: %lldμs\t~%lld fps%s\n",
		C_CRIMSON, t, 1000000L / t, RESET);
}

static void	_do_move(t_time *t1, t_render *render)
{
	_check_for_move((t1->tv_sec - render->keys.last_move.tv_sec) * 1000000L
		+ (t1->tv_usec - render->keys.last_move.tv_usec), render);
	_check_for_rotate((t1->tv_sec - render->keys.last_rotate.tv_sec) * 1000000L
		+ (t1->tv_usec - render->keys.last_rotate.tv_usec), render);
}

static void	_check_for_move(long long t, t_render *render)
{
	if (t < MOVE_TICK)
		return ;
	if (gettimeofday(&render->keys.last_move, NULL) == -1)
	{
		puterr("Unexpected error on gettimeofday.", false, false);
		quit(render);
	}
	move_player(&render->game, render->keys.pressed);
}

static void	_check_for_rotate(long long t, t_render *render)
{
	if (t < ROTATE_TICK)
		return ;
	if (gettimeofday(&render->keys.last_rotate, NULL) == -1)
	{
		puterr("Unexpected error on gettimeofday.", false, false);
		quit(render);
	}
	if (render->keys.pressed[INDEX_CAMERA_RIGHT])
	{
		render->game.dir += SENSITIVITY;
		if (render->game.dir > (2 * PI))
			render->game.dir -= (2 * PI);
	}
	if (render->keys.pressed[INDEX_CAMERA_LEFT])
	{
		render->game.dir -= SENSITIVITY;
		if (render->game.dir < 0)
			render->game.dir += (2 * PI);
	}
}
