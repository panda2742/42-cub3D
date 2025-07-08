/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_engine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:36:42 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/08 19:13:50 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_ENGINE_H
# define GRAPHIC_ENGINE_H

typedef struct	s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct	s_ivec2
{
	long int	x;
	long int	y;
}	t_ivec2;

t_vec2	vec2(double x, double y);
t_ivec2	ivec2(long int x, long int y);

#endif