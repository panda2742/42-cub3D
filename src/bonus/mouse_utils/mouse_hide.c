/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:43:48 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/20 18:52:27 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mouse_danger.h"

void	mouse_hide(t_render *render)
{
	t_xvar		*var;
	t_win_list	*win;

	var = (t_xvar *)render->mlx;
	win = (t_win_list *)render->mlx_win;
	XFixesHideCursor(var->display, win->window);
}
