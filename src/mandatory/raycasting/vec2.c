/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:40:43 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 09:57:41 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_vec2	vec2(double x, double y)
{
	return ((t_vec2){.x = x, .y = y});
}

t_ivec2	ivec2(long int x, long int y)
{
	return ((t_ivec2){.x = x, .y = y});
}
