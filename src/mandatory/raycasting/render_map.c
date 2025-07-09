/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:38:28 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/09 19:32:40 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	map_data[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	render_map(void)
{
	// Vecteur position joueur
	t_vec2	pos = vec2(22, 12);
	// Vecteur direction du joueur
	t_vec2	dir	= vec2(-1, 0);
	// Version 2D raycast-ed d'un plan camera pour le FOV
	t_vec2	plane = vec2(0, 0.66);

	// Juste pour gerer les FPS et la vitesse de rendu
	// double	time = 0, oldTime = 0;

	size_t	x = 0;
	double	w = (double)SCREEN_WIDTH;
	double	h = (double)SCREEN_HEIGHT;
	while (x < w)
	{
		// Colonne/pixel qui dirigera le rayon associe a l'iteration
		double	camX = 2 * x / w - 1;

		// La direction du rayon que l'on lance
		t_vec2	rayDir = vec2(dir.x + plane.x * camX, dir.y + plane.y * camX);

		// Les coordonnées de la case de la map où pos se trouve (partie intégrale)
		t_ivec2	map = ivec2((int)pos.x, (int)pos.y);

		// Longueur du rayon depuis pos jusqu'au prochain x et y
		t_vec2	sideDist = vec2(0, 0);

		// Longueur du rayon depuis un côté x ou y jusqu'au prochain côté x ou y
		t_vec2	deltaDist = vec2(
			(rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x),
			(rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y)
		);
		double	perpWallDist;

		// Direction dans laquelle on va step dans chaque dimension x y (-1 ou +1)
		t_ivec2	step = ivec2(
			1 - 2 * (rayDir.x < 0),
			1 - 2 * (rayDir.y < 0)
		);

		// Un mur a été touché ?
		unsigned char	hit = 0;
		// C'était quoi ? Un mur NS (ordonnées) ou EW (abscisses) ?
		unsigned char	side;

		// Calcul du step initial et de la distance side
		if (rayDir.x < 0)
			sideDist.x = (pos.x - map.x) * deltaDist.x;
		else
			sideDist.x = (map.x + 1.0 - pos.x) * deltaDist.x;
		if (rayDir.y < 0)
			sideDist.y = (pos.y - map.y) * deltaDist.y;
		else
			sideDist.y = (map.y + 1.0 - pos.y) * deltaDist.y;

		// Magie du DDA
		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = 1;
			}

			// Vérification si le rayon a touché un mur
			if (map_data[map.x][map.y] > 0) hit = 1;

			// On calcule la distance projetée depuis la direction caméra (sans fisheye)
			if (side == 0)
				perpWallDist = (sideDist.x - deltaDist.x);
			else
				perpWallDist = (sideDist.y - deltaDist.y);

			// Calculons la hauteur de la ligne à dessiner
			int	lineHeight = (int)(h / perpWallDist);

			// Calculons le pixel le plus haut et le plus bas pour remplir la ligne
			int	drawStart = -lineHeight / 2 + h / 2;
			if (drawStart < 0)
				drawStart = 0;
			int	drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;
			
			printf("%d\t%d\n", drawStart, drawEnd);
		}
		x++;
	}
}
