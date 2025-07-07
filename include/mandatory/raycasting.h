/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:29:35 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/07 17:43:12 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3D.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int		(*test_world_map(void))[MAP_WIDTH];
void	render_map(int (*map)[MAP_WIDTH]);

#endif