/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:08:28 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/06 02:18:52 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CUB_FILE_H
# define PARSE_CUB_FILE_H
# define MALLOC_ERROR -1
# define INVALID_CONFIG -2
# define FILE_EMPTY -3
# define OPEN_ERROR -3


#include "cub3D.h"


typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
} t_textures;

typedef struct s_colors
{
	int *ceil;
	int *floor;
} t_colors;

typedef struct s_data
{
	t_textures textures;
	t_colors colors;
	char **map;
} t_data;

//avirer
int free_array(char **array);


//parse_cub_file.c
int parse_cub_file(char *map, t_data *data);
int free_data(t_data *data);

//is_valid_map_path.c
int parsing_error_handler(t_data *data, int exit_code);
int get_file_content(char ***file_content, int fd, int size);
int is_valid_file(char *map);
int get_file_size(char *map);
int is_valid_map_path(char *map, char ***file_content);

//get_map_textures.c // a virer ?
int get_map_textures(t_data *data, char ***file_content);
bool get_textures_from_file(char ***file_content);
bool are_textures_valid(t_data *data, char ***file_content, int i);
int fill_textures_data(t_data *data, char ***file_content, int i);
int add_texture(t_data *data, char *line);
int dup_texture_path(char *dest, char *line);
int get_texture_path(char *line);
bool is_a_texture_declaration(char *line);

//init_data_textures.c
// int interpet_texture(t_data *data, char *line);
int init_textures(t_data *data, char **file_content, int i);
int is_texture_declaration(char *line);

//init_color.c
int init_colors(t_data *data, char **file_content, int i);
int is_color_declaration(char *line);

//init_data_map.c
int is_valid_map(char **map);
int get_map(t_data *data, char **file_content, int i);

//parse_cub_file.c
int parse_cub_file(char *map, t_data *data);
int print_cub_data(t_data *data);

#endif
