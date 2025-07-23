/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_warp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:44:07 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 19:28:36 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mouse_danger.h"

void	mouse_warp(t_render *render)
{
	t_xvar		*var;
	t_win_list	*win;

	var = (t_xvar *)render->mlx;
	win = (t_win_list *)render->mlx_win;
	XWarpPointer(var->display, None, win->window, 0, 0, 0, 0,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
