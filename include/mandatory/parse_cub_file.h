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

#include "cub3D.h"

//is_valid_map_path.c
int parsing_error_handler(char *map, t_data *data);
int get_file_content(char *map, char ***file_content, int fd, int size);
int is_valid_file(char *map);
int get_file_size(char *map, int fd);
int is_valid_map_path(char *map, char ***file_content);

//get_map_textures.c
int get_map_textures(t_data *data, char ***file_content);
bool get_textures_from_file(char ***file_content);
bool are_textures_valid(t_data *data, char ***file_content, int i);
int fill_textures_data(t_data *data, char ***file_content, int i);
int add_texture(t_data *data, char *line);
int dup_texture_path(char *dest, char *line);
int get_texture_path(char *line);
bool is_a_texture_declaration(char *line);

//parse_cub_file.c
int parse_cub_file(char *map, t_data *data);
int print_cub_data(t_data *data);

#endif PARSE_CUB_FILE_H
