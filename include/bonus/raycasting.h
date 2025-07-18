/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:29:35 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/18 14:32:52 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3D.h"
# include <math.h>
# include <sys/time.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 800

# define VELOCITY 0.1
# define SENSITIVITY 0.01
# define PI 3.14159265359f
# define FOV_FACTOR 1.0471975512f
# define HITBOX_HALFSIZE 0.2
# define MOVE_TICK 10000
# define ROTATE_TICK 100

# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

# define FACE_NORTH 0
# define FACE_SOUTH 1
# define FACE_EAST 2
# define FACE_WEST 3
# define FACE_VERTICAL 0
# define FACE_HORIZONTAL 1

# define KEY_FORWARD 'w'
# define INDEX_FORWARD 0

# define KEY_LEFT 'a'
# define INDEX_LEFT 1

# define KEY_BACKWARD 's'
# define INDEX_BACKWARD 2

# define KEY_RIGHT 'd'
# define INDEX_RIGHT 3

# define KEY_CAMERA_LEFT 65361
# define INDEX_CAMERA_LEFT 4

# define KEY_CAMERA_RIGHT 65363
# define INDEX_CAMERA_RIGHT 5

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
 * Represent a pair of int values, used for integer pairs (integer
 * coordinates for example).
 */
typedef struct s_ivec2
{
	int	x;
	int	y;
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
	 * The color of the ceiling.
	 */
	int		c_color;
	/**
	 * The amount of lines the map has.
	 */
	int		height;
	/**
	 * The lengths of each line of the map.
	 */
	size_t	*lengths;
	/**
	 * The color of the floor.
	 */
	int		f_color;
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
 * Represent the keys pressed or not during the gameplay to make our own
 * keyrepeat system (avoiding the MLX one).
 */
typedef struct s_keys
{
	/**
	 * The last time the player moved.
	 */
	t_time	last_move;
	/**
	 * The last time the player moved the camera.
	 */
	t_time	last_rotate;
	/**
	 * The state of each keys.
	 * 0 - w
	 * 1 - a
	 * 2 - s
	 * 3 - d
	 * 4 - left_arrow
	 * 5 - right_arrow
	 */
	char	pressed[6];
}			t_keys;

/**
 * Represent a sprite displayed on the screen, with its animation.
 */
typedef struct s_sprite
{
	/**
	 * The amout of frames the sprite has.
	 */
	size_t	frames;
	/**
	 * The data image of each frame of the sprite.
	 */
	t_img	*data;
	/**
	 * The data frame of each frame of the sprite.
	 */
	t_frame	*fdata;
	/**
	 * The amount of time between each frame.
	 */
	double	interval;
	/**
	 * The last time the frame was generated.
	 */
	t_time	last;
	/**
	 * The id of the current frame.
	 */
	size_t	current;
	/**
	 * The position on the display.
	 */
	t_ivec2	pos;
}			t_sprite;

/**
 * The used data for the whole rendering process.
 */
typedef struct s_render
{
	/**
	 * Pointer to MLX instance.
	 */
	void		*mlx;
	/**
	 * Pointer to MLX window.
	 */
	void		*mlx_win;
	/**
	 * The data of the current calculated frame.
	 */
	t_frame		frame;
	/**
	 * The game data (including the map and the player position).
	 */
	t_gdata		game;
	/**
	 * The textures of each wall face.
	 */
	t_img		textures[4];
	/**
	 * The keys state for the gameplay.
	 */
	t_keys		keys;
	/**
	 * The sprite (samurai) of the scene.
	 */
	t_sprite	sprite;
	/**
	 * Represent the minimap of the game.
	 */
	t_frame		mini_frame;
	/**
	 * Represent the minimap of the game, but its image data.
	 */
	t_img		mini_img;
}	t_render;

/**
 * Represent all the datas of an emitted ray. This structure is just gathering
 * the most used data for a ray path. Its purpose is optimization only.
 */
typedef struct s_rayctx
{
	double	w;
	double	h;
	int		*frame_addr;
	t_vec2	dir;
	t_vec2	plane;
	double	cam_x;
	t_vec2	ray_dir;
	t_ivec2	map_def;
	t_ivec2	map;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	double	perp_dist;
	t_ivec2	step;
	int		face;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_vec2	pos;
	int		c_color;
	int		f_color;
	double	wall_x;
	char	texture_index;
	int		texture_x;
	int		texture_y;
}			t_rayctx;

typedef enum e_direction
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
}	t_direction;

void	move_player(t_gdata *game, char pressed[6]);
void	render_map(t_render *render);
void	draw_frame(t_render *render);
char	check_collision(t_gdata *game, t_vec2 new);
int		destroy_hook(t_render *render);
void	quit(t_render *render);
int		loop_hook(t_render *render);
char	dda_algorithm(t_render *render, t_rayctx *ctx, int x);
int		keydown_hook(int keycode, t_render *render);
int		keyup_hook(int keycode, t_render *render);
int		focusout_hook(t_render *render);
void	load_sprite(t_render *render);
void	draw_sprite(t_render *render);
void	init_minimap(t_render *render);
void	draw_minimap(t_render *render);

#endif
