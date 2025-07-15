/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:10:33 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 17:50:59 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_frame(t_render *render)
{
	size_t	x;

	x = 0;
	
	t_vec2 dir = vec2(cos(render->game.dir), sin(render->game.dir));
	double plane_x = -dir.y * FOV_FACTOR;
	double plane_y = dir.x * FOV_FACTOR;

    int blue = rgba(100, 200, 250, 1);
    int pink = rgba(255, 0, 255, 1);
    int yellow = rgba(255, 255, 0, 1);
    int brown = rgba(153, 80, 12, 1);

	while (x < SCREEN_WIDTH)
	{
		double camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;

        double ray_dir_x = dir.x + plane_x * camera_x;
        double ray_dir_y = dir.y + plane_y * camera_x;

        int map_x = (int)render->game.pos.x;
        int map_y = (int)render->game.pos.y;

        double side_dist_x, side_dist_y;
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;
        char step_x = 1 - (2 * (ray_dir_x < 0)), step_y;

        // Calcul du step et de la distance initiale à la prochaine side
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (render->game.pos.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - render->game.pos.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (render->game.pos.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - render->game.pos.y) * delta_dist_y;
        }

        // DDA
        int side;
        while (1)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map_x < 0 || map_y < 0
                || map_x >= (int)(render->game.map.width)
                || map_y >= (int)(render->game.map.height))
                break;
            if (render->game.map.data[map_y][map_x] == '1')
                break ;
        }
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);

        // Calcul de la hauteur de la colonne
		if (side == 0)
			perp_wall_dist = (map_x - render->game.pos.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - render->game.pos.y + (1 - step_y) / 2) / ray_dir_y;
        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

        // Ici, dessine la colonne verticale à x de draw_start à draw_end
		int y = 0;
        while (y < draw_start)
            put_pixel_on_frame(&render->frame, x, y++, blue);
        y = draw_start;
		if (y < 0) y = 0;
		if (draw_end > SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT;
		while (y < draw_end)
		{
			int color = yellow;
			if (side)
				color = pink;
			put_pixel_on_frame(&render->frame, x, y, color);
			y++;
		}
        y = draw_end;
        while (y < SCREEN_HEIGHT)
            put_pixel_on_frame(&render->frame, x, y++, brown);
		x++;
	}
	mlx_put_image_to_window(render->mlx, render->mlx_win, render->frame.img, 0, 0);
}
