/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:36:17 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/17 16:42:54 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	focusout_hook(t_render *render)
{
	size_t	i;

	i = -1;
	while (++i < 6)
		render->keys.pressed[i] = 0;
	return (0);
}
