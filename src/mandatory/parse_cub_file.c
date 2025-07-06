/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:18:59 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/06 07:54:09 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cub_file.h"

int init_textures(t_data *data, char **file_content, int i)
{
  if (!ft_strncmp(file_content[i], "NO", 2) && file_content[i][2] == ' ')
    return (init_textures_north(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "SO", 2) && file_content[i][2] == ' ')
    return (init_textures_south(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "SO", 2) && file_content[i][2] == ' ')
    return (init_textures_west(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "SO", 2) && file_content[i][2] == ' ')
    return (init_textures_east(data, file_content[i]));
  else
    return (INVALID_CONFIG);
  return (0);
}

int init_colors(t_data *data, char **file_content, int i)
{
  if (!ft_strncmp(file_content[i], 'C', 1) && file_content[i][1] == ' ') 
    return (init_color_ceil(data, file_content[i]));
  if (!ft_strncmp(file_content[i], 'F', 1) && file_content[i][1] == ' ') 
    return (init_color_ceil(data, file_content[i]));
  else
    return (INVALID_CONFIG);
  return (0);
}

int get_map(t_data *data, char **file_content, int i)
{
  return (0);
}

int is_a_texture_declaration(t_data *data, char *line)
{
  char **key_value;
  int exit_code;

  exit_code = 0;
  key_value = ft_split(line, ' ');
  if (!key_value)
    return (MALLOC_ERROR);
  if (key_value[0] && 
      (!ft_strncmp(key_value[0], "NO", 2) ||
       !ft_strncmp(key_value[0], "SO", 2) ||
       !ft_strncmp(key_value[0], "WE", 2) ||
       !ft_strncmp(key_value[0], "EA", 2)))
  {
    if (key_value[1] && !key_value[2] && 
      !ft_strncmp(key_value[1][ft_strlen(key_value[1]) - 4], ".xmp", 5) &&
      access(key_value[1], F_OK | R_OK) == 0)
      exit_code = 1;
  }
  free_array(key_value);
  return (exit_code);
}

bool check_color_values(char **colors)
{
  int i;
  int n;

  while (colors[i])
  {
    n = ft_atoi(colors[i]);
    if (n < 0 || n > 255)
      return (false);
    i++;
  }
  return (true);
}

int is_a_color_declaration(t_data *data, char *file_content)
{
  char **key_value;
  char **color;
  int exit_code;

  exit_code = 0;
  key_value = ft_split(line, ' ');
  if (key_value[0] && 
      (!ft_strncmp(key_value[0], "C", 1) ||
       !ft_strncmp(key_value[0], "F", 1)))
  {
    if (key_value[1] && !key_value[2])
    {
      color = ft_split(key_value[1], ',');
      if (color[0] && color[1] && color[2] && !color[3])
      {
        if (check_color_values(color)) 
          exit_code = 1;
        free_array(color);
      }
    }
  }
  free_array(key_value);
  return (exit_code);
}

int is_a_map_declaration(t_data *data, char **file_content)
{
  //si la ligne contient des espaces ou des 0 des 1 ou un N
  //un boolen pour N
  //si jusqu'a la fin du fichier on a la map
  //checker le contour de la map
  //
}

int interpret_line(t_data *data, char **file_content)
{
  if (is_a_texture_declaration(file_content[i]))
  {
    if (data->textures->north || data->textures->south || data->textures->west || data->textures->east)
      return (INVALID_CONFIG);
    return (init_textures(data, file_content, i));
  }
  else if (is_a_color_declaration(file_content[i]))
  {
    if (data->color->ceil || data->color->floor)
      return (INVALID_CONFIG); 
    return (init_colors(data, file_content, i));
  }
  else if (is_map_declaration(file_content[i]))
  {
    if (data->maps)
      return (INVALID_CONFIG);
    return (get_map(data, file_content, i));
  }
  else 
    return (INVALID_CONFIG);
  return (0);
}

int init_data(t_data *data, char **file_content)
{
  int i;

  i = 0;
  ft_bzero(data, sizeof(data));
  while (file_content[i])
  {
    i = interpret_line(data, file_content);
    if (i < 0)
    {
      free_data(data);
      return (i);
    }
    i++;
  }
  return (0);
}

int parse_cub_file(char *map, t_data *data)
{
  char **file_content;
  int exit_code;

  if (is_valid_map_path(map, &file_content))
    return (parsing_error_handler(data, &file_content));
  exit_code = init_data(data, file_content);
  if (exit_code != 0)
    return (exit_code);
  /* if (get_map_textures(data)) */
  /*   return (parsing_error_handler(data)); */
  /* if (get_colors_(data)) */
  /*   return (parsing_error_handler(data)); */
  /* if (get_map(data)) */
  /*   return (parsing_error_handler(data)); */
  return (0);
}
