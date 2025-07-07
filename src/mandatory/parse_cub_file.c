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

int interpet_texture(char *line)
{
  if (!ft_strncmp(file_content[i], "NO", 2) && file_content[i][2] == ' ' && !data->textures->north)
    return (init_textures_north(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "SO", 2) && file_content[i][2] == ' ' && !data->textures->south)
    return (init_textures_south(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "WE", 2) && file_content[i][2] == ' ' && !data->textures->west)
    return (init_textures_west(data, file_content[i]));
  else if (!ft_strncmp(file_content[i], "EA", 2) && file_content[i][2] == ' ' && !data->textures->east)
    return (init_textures_east(data, file_content[i]));
  else
    return (INVALID_CONFIG);
}

int init_textures(t_data *data, char **file_content, int i)
{
  int exit_code;

  while (file_content[i] && is_texture_declaration(file_content[i]))
  {
    exit_code = interpet_texture(file_content[i]);
    i++;
  }
  if (data->textures->north && data->textures->south && data->textures->west && data->textures->east)
    return (i);
  return (INVALID_CONFIG);
}

int get_color_code(char *line, int color_code[3])
{
  int i;
  char **splitted;

  i = 1;
  while (line[i] && line[i] == ' ')
    i++;
  splitted = ft_split(line + i, ',');
  if (splitted[0] && splitted[1] && splitted[2] && !splitted[3] &&
      is_only_digits(splitted[0] && is_only_digits(splitted[1] && is_only_digits(splitted[2])))
  {
    color_code[0] = ft_atoi(splitted[0]);
    color_code[1] = ft_atoi(splitted[1]);
    color_code[2] = ft_atoi(splitted[2]);
    free_array(splitted);
    if (color_code[0] < 0 || color_code[0] > 255 || 
        color_code[1] < 0 || color_code[1] > 255 ||
        color_code[2] < 0 || color_code[2] > 255)
      return (INVALID_CONFIG);
    else
      return (0);
  }
  else 
    return (INVALID_CONFIG);
}

int init_colors(t_data *data, char **file_content, int i)
{
  if (!ft_strncmp(file_content[i], 'C', 1) && file_content[i][1] == ' ' && !data->color->ceil) 
    return(get_color_code(file_content[i], data->color->ceil));
  if (!ft_strncmp(file_content[i], 'F', 1) && file_content[i][1] == ' ' && !data->color->floor) 
    return(get_color_code(file_content[i], data->color->floor));
  else
    return (INVALID_CONFIG);
  return (0);
}

int is_texture_declaration(t_data *data, char *line)
{
  char **key_value;
  int exit_code;

  exit_code = 0;
  key_value = ft_split(line, ' ');
  if (!key_value)
    return (MALLOC_ERROR);
  if (key_value[0] && 
      (!ft_strncmp(key_value[0], "NO", 3) ||
       !ft_strncmp(key_value[0], "SO", 3) ||
       !ft_strncmp(key_value[0], "WE", 3) ||
       !ft_strncmp(key_value[0], "EA", 3)))
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

int is_color_declaration(t_data *data, char *file_content)
{
  char **key_value;
  char **color;
  int exit_code;

  exit_code = 0;
  key_value = ft_split(line, ' ');
  if (key_value[0] && 
      (!ft_strncmp(key_value[0], "C", 2) ||
       !ft_strncmp(key_value[0], "F", 2)))
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

int get_map(t_data *data, char **file_content, int i)
{
  int j;

  j = 0;
  while (file_content[i])
  {
    ft_strdup(data->map[j], file_content[i]);
    if (!data->map[j])
    {
      //free map a rebour
      return (MALLOC_ERROR);
    }
    i++;
    j++;
  }
  data->map[j] = NULL;
  if (!is_map_closed_by_walls(data->map))
}

int is_map_declaration(t_data *data, char **file_content, int i, bool player)
{
  int j;

  j = 0;
  while (file_content[i][j])
  {
    if (file_content[i][j] == ' ' || file_content[i][j] == '0' || file_content[i][j] == '1' || (file_content[i][j] == 'N' && player = false))
    {
      if (file_content[i][j] == 'N')
        player = true;
    }
    j++;
  }
  if (file_content[i][j])
    return (INVALID_CONFIG);
  if (file_content[i + 1])
    return (is_map_declaration(data, file_content, i + 1, player));
  else 
    return (1);
}

int check_player(char **map)
{
  int i;
  int j;
  bool player;

  player = false;
  while (map[i])
  {
    while (map[i][j])
    {
      if (map[i][j] == 'N')
      {
        if (player == true)
          return (INVALID_CONFIG);
        else
          player = true;
      }
      j++;
    }
    i++;
  }
  if (player)
    return (true);
  return (false);
}

int check_closed_map(char **map)
{
  //murs ?
  //comment on interprete les espaces ?
}

int is_valid_map(char **map)
{
  if (!check_player(map) || !check_closed_map(map))
    return (INVALID_CONFIG);
  else
    return (1);
}

int get_map(t_data *data, char **file_content, int i)
{
  int j;

  j =0;
  while (file_content[i])
  {
    ft_strdup(data->maps[j], file_content[i]);
    if (!data->maps[j])
    {
      while (j - 1 >= 0)
      {
        free(data->maps[j - 1]);
        j--;
      }
      return (MALLOC_ERROR);
    }
    j++;
    i++;
  }
  return (0);
}

int interpret_line(t_data *data, char **file_content)
{
  if (is_texture_declaration(file_content[i]))
  {
    if (data->textures->north || data->textures->south || data->textures->west || data->textures->east)
      return (INVALID_CONFIG);
    return (init_textures(data, file_content, i));
  }
  else if (is_color_declaration(file_content[i]))
  {
    if (data->color->ceil || data->color->floor)
      return (INVALID_CONFIG); 
    return (init_colors(data, file_content, i));
  }
  else if (is_map_declaration(data, file_content, i, false))
  {
    //si : 
    //- la ligne correspond a une ligne de map
    //si toutes les lignes qui suivent correspondent un des lignes de map
    //si fin de fichier : 
    //OUI
    if (data->maps)
      return (INVALID_CONFIG);
    //on recuperer la map en copiant toute la fin du fichier
    exit_code = get_map(data, file_content, i);
    if (exit_code < 0)
      return (exit_code);
    //on controle la map
    return (is_valid_map(data->map));
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
  while (file_content[i] && !data->map)
  {
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
    i = interpret_line(data, file_content);
    if (i < 0)
    {
      free_data(data);
      return (i);
    }
  }
  return (0);
}

int parsing_error_handler(char *map, t_data *data, int exit_code)
{
  printf("Error\n");
  //free ici
  return (exit_code);
}

int parse_cub_file(char *map, t_data *data)
{
  char **file_content;
  int exit_code;

  exit_code = is_valid_map_path(map, &file_content);
  if (exit_code != 0)
    return (parsing_error_handler(data, &file_content, exit_code));
  exit_code = init_data(data, file_content);
  if (exit_code != 0)
    retrun (parsing_error_handler(data, &file_content, exit_code));
  return (0);
}
