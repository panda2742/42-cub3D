/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/07 18:52:19 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	render_map(int (*map)[MAP_WIDTH])
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	mlx_loop(mlx);

	double posX = 22, posY = 12; // x and y start position
	double dirX = -1, dirY = 0; // initial direction vector
	double planeX = 0, planeY = 0.66; // the 2nd raycaster version of camera plane

	double time = 0, oldTime = 0; // time of current and previous frame
	
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY + cameraX;

	}
	
	(void)map;
}
