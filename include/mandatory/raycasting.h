/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:29:35 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/15 10:02:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3D.h"
# include <math.h>
# include <sys/time.h>

# define SCREEN_WIDTH 960
# define SCREEN_HEIGHT 540

# define VELOCITY 0.1
# define SENSITIVITY 0.2
# define PI 3.14159265359f
# define FOV_FACTOR 0.66f

# define KEY_FORWARD 'w'
# define KEY_LEFT 'a'
# define KEY_BACKWARD 's'
# define KEY_RIGHT 'd'
# define KEY_CAMERA_LEFT 65361
# define KEY_CAMERA_RIGHT 65363
# define KEY_ESCAPE 65307

typedef struct timeval	t_time;

/**
 * Represent an image rendered onto the MLX window.
 */
typedef struct s_frame
{
	/**
	 * The pointer of the image.
	 */
	void	*img;
	/**
	 * The address of the data of the image.
	 */
	char	*addr;
	/**
	 * As the pixels are basically ints, these usually are 4 bytes (one per
	 * channel)
	 */
	int		bits_per_pixel;
	/**
	 * Refer to the length of the data sequence into the memory.
	 */
	int		line_length;
	/**
	 * Refer to how the bytes are stored into the computer (can infer with the
	 * display of the image for example for 8 bits remote displays).
	 */
	int		endian;
}			t_frame;

/**
 * Represent a texture or an image in general from an XPM file.
 */
typedef struct s_img
{
	/**
	 * The name of the file including the texture.
	 */
	char	*filename;
	/**
	 * The pointer of the data of the image (from MLX).
	 */
	void	*ptr;
	/**
	 * The width of the image.
	 */
	int		width;
	/**
	 * The height of the image.
	 */
	int		height;
}	t_img;

/**
 * Represent a pair of double values, used for dots or vectors.
 */
typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

/**
 * Represent a pair of long int values, used for integer pairs (integer
 * coordinates for example).
 */
typedef struct s_ivec2
{
	long int	x;
	long int	y;
}	t_ivec2;

/**
 * Represent the data of the rendered map (basically its content).
 */
typedef struct s_map
{
	/**
	 * Each line of the map, without any modification from the parsing.
	 */
	char	**data;
	/**
	 * The width of the table.
	 */
	size_t	width;
	/**
	 * The height of the table.
	 */
	size_t	height;
}			t_map;

/**
 * The data of the game.
 */
typedef struct s_gdata
{
	/**
	 * The current player position. A dot or a 0->pos vector.
	 */
	t_vec2	pos;
	/**
	 * The orientation of the camera. Represent the angle mesure in rad.
	 */
	double	dir;
	/**
	 * The orientation of the player at the beginning of the game.
	 */
	char	orientation;
	/**
	 * The map of the game.
	 */
	t_map	map;
}			t_gdata;

/**
 * The used data for the whole rendering process.
 */
typedef struct s_render
{
	/**
	 * Pointer to MLX instance.
	 */
	void	*mlx;
	/**
	 * Pointer to MLX window.
	 */
	void	*mlx_win;
	/**
	 * The data of the current calculated frame.
	 */
	t_frame	frame;
	/**
	 * The game data (including the map and the player position).
	 */
	t_gdata	game;
	/**
	 * The last frame generation timestamp.
	 */
	t_time	t;
	/**
	 * The textures of each wall face.
	 */
	t_img	textures[4];
}	t_render;

/**
 * Generate a new 2D vector (can be used as a pair of doubles).
 * 
 * @param x The x value.
 * @param y The y value.
 * @returns A 2D vector instance.
 */
t_vec2			vec2(double x, double y);

/**
 * Generate a new 2D integer vector (can be used as a pair of long integers).
 * 
 * @param x The x value.
 * @param y The y value.
 * @returns A 2D integer vector instance.
 */
t_ivec2			ivec2(long int x, long int y);

typedef enum e_direction
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
}	t_direction;

unsigned int	rgba(
					unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
void			put_pixel_on_frame(t_frame *img, int x, int y, int rgba);
void			render_map(void);
void			draw_frame(t_render *render);

int				key_hook(int keycode, t_render *render);
int				destroy_hook(t_render *render);
void			quit(t_render *render);
t_vec2			move_player(t_gdata *game, t_direction dir);
void			pos_update(t_gdata *game, t_vec2 new);
char			pos_tile(t_gdata *game);

#endif
