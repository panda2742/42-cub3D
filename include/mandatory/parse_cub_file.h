/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:08:28 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/19 15:25:30 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CUB_FILE_H
# define PARSE_CUB_FILE_H
# define MALLOC_ERROR -1
# define INVALID_CONFIG -2
# define FILE_EMPTY -3
# define OPEN_ERROR -3

# include "cub3D.h"

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_textures;

typedef struct s_colors
{
	int			*ceil;
	int			*floor;
}				t_colors;

typedef struct s_map_infos
{
	char		**grid;
	int			height;
	double		spawn_position[2];
	char		spawn_orientation;
}				t_map_infos;

typedef struct s_data
{
	t_textures	textures;
	t_colors	colors;
	t_map_infos	map;
}				t_data;

// parse_cub_file.c
int				parse_cub_file(char *map, t_data *data);

// is_valid_map_path.c
int				is_valid_map_path(char *map, char ***file_content);

// init_data_map.c
int				is_valid_map(t_data *data);
int				get_map(t_data *data, char **file_content, int i);

// init_data_map_utils.c
int				is_valid_map_format(t_data *data, t_bool *player);

// parse_cub_file.c
int				parse_cub_file(char *map, t_data *data);
int				print_cub_data(t_data *data);

// parse_cub_file_utils.c
int				check_data(t_data *data);
int				is_only_digits(char *str);
int				free_array(char **array);
int				free_data(t_data *data);
int				parsing_error_handler(t_data *data, int exit_code);

// is_valid_map_path.c
int				is_valid_map_path(char *map, char ***file_content);

// interpret_line.c
int				interpret_line(t_data *data, char **key_value, char **color_code);

#endif
