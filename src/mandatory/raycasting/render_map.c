/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/08 19:23:47 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	render_map(int (*map_data)[MAP_WIDTH])
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");

	// Vecteur position joueur
	t_vec2	pos = vec2(22, 12);
	// Vecteur direction du joueur
	t_vec2	dir	= vec2(-1, 0);
	// Version 2D raycast-ed d'un plan camera pour le FOV
	t_vec2	plane = vec2(0, 0.66);

	// Juste pour gerer les FPS et la vitesse de rendu
	double	time = 0, oldTime = 0;

	size_t	x = 0;
	double	w = (double)SCREEN_WIDTH;
	while (x < w)
	{
		// Colonne/pixel qui dirigera le rayon associe a l'iteration
		double	camX = 2 * x / w - 1;

		t_vec2	rayDir = vec2(dir.x + plane.x * camX, dir.y + plane.y * camX);

		x++;
	}

	(void)map_data;
	mlx_loop(mlx);
}
