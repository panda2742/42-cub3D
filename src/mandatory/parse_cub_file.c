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

#include "../../include/mandatory/parse_cub_file.h"

/* int free_data(t_data *data) */
/* { */
/*   if (data->textures.north) */
/*     free(data->textures.north); */
/*   if (data->textures.south) */
/*     free(data->textures.south); */
/*   if (data->textures.south) */
/*     free(data->textures.west); */
/*   if (data->textures.west) */
/*     free(data->textures.west); */
/*   if (data->textures.east) */
/*     free(data->textures.east); */
/*   if (data->map) */
/*     free_array(data->map); */
/*   return (0); */
/* } */

int parsing_error_handler(t_data *data, int exit_code)
{
  (void)data;
  printf("Error\n");
  /* free_data(data); */
  return (exit_code);
}

int load_texture(char *slot, char **key_value)
{
  slot = ft_strdup(key_value[1]);
  if (!slot)
  {
    free_array(key_value);
    return (MALLOC_ERROR);
  }
  free_array(key_value);
  return (0);
}

int is_only_digits(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] < '0' || str[i] > '9')
      return (0);
    i++;
  }
  return (1);
}

int interpret_texture(t_data *data, char **key_value)
{
  if (!ft_strncmp(key_value[0], "NO", 3) && !data->textures.north)
    return (load_texture(data->textures.north, key_value));
  if (!ft_strncmp(key_value[0], "SO", 3) && !data->textures.south)
    return (load_texture(data->textures.south, key_value));
  if (!ft_strncmp(key_value[0], "WE", 3) && !data->textures.west)
    return (load_texture(data->textures.west, key_value));
  if (!ft_strncmp(key_value[0], "EA", 3) && !data->textures.east)
    return (load_texture(data->textures.east, key_value));
  return (INVALID_CONFIG);
}

int load_color(int *slot, char **color_code, char **key_value)
{
  slot = malloc(sizeof(int) * 3);
  if (!slot)
  {
    free_array(color_code);
    free_array(key_value);
    return (MALLOC_ERROR);
  }
  slot[0] = ft_atoi(color_code[0]);
  slot[1] = ft_atoi(color_code[1]);
  slot[2] = ft_atoi(color_code[2]);
  free_array(color_code);
  free_array(key_value);
  if (slot[0] < 0 || slot[0] > 255 || 
      slot[1] < 0 || slot[1] > 255 ||
      slot[2] < 0 || slot[2] > 255)
    return (INVALID_CONFIG);
  return (0);
}

int interpret_color(t_data *data, char **key_value, char **color_code)
{
  if (color_code[0] && color_code[1] && color_code[2] && !color_code[3] &&
  is_only_digits(color_code[0]) &&
  is_only_digits(color_code[1]) && 
  is_only_digits(color_code[2])) 
  {
    if (!ft_strncmp(key_value[0], "C", 2) && !data->colors.ceil)
      return (load_color(data->colors.ceil, color_code, key_value));
    if (!ft_strncmp(key_value[0], "F", 2) && !data->colors.floor)
      return (load_color(data->colors.floor, color_code, key_value));
  }
  return (INVALID_CONFIG);
}

int interpret_line(t_data *data, char *line)
{
  char **key_value;
  char **color_code;

  printf("line = %s\n", line);
  key_value = ft_split(line, ' ');
  if (!key_value)
    return (MALLOC_ERROR);
  if (key_value[0] && key_value[1] && !key_value[2])
  {
    if (ft_strlen(key_value[0]) == 2 && ft_strlen(key_value[1]) >= 5 &&
      !ft_strncmp(key_value[1] + ft_strlen(key_value[1]) - 5, ".xmp\n", 6))
      return (interpret_texture(data, key_value));
    else if (ft_strlen(key_value[1]) == 1)
    {
      color_code = ft_split(key_value[1], ',');
      return (interpret_color(data, key_value, color_code));
    }
  }
  printf("%ld %s %d\n", ft_strlen(key_value[0]), key_value[1] + (ft_strlen(key_value[1]) - 5), (ft_strncmp(key_value[1] + ft_strlen(key_value[1]) - 4, ".xmp", 4)));
  return (INVALID_CONFIG);
  /* if (is_texture_declaration(file_content[i])) */
  /* { */
  /*   if (data->textures.north || data->textures.south || data->textures.west || data->textures.east) */
  /*     return (INVALID_CONFIG); */
  /*   return (init_textures(data, file_content, i)); */
  /* } */
  /* else if (is_color_declaration(file_content[i])) */
  /* { */
  /*   if (data->colors.ceil[0] || data->colors.ceil[1] || data->colors.ceil[2] || */
  /*     data->colors.floor[0] || data->colors.floor[1] || data->colors.floor[2])  */
  /*     return (INVALID_CONFIG);  */
  /*   return (init_colors(data, file_content, i)); */
  /* } */
  /* else  */
  /*   return (INVALID_CONFIG); */
  /* return (0); */
}

/* for each line of the config file : 
 * - skip \n
 * - interpet if it's color / textures declaration 
 *   - YES : init declared data
 *   - NO : invalid config
 * - if all data are set there should be left only the map or extra \n in config file
 *   any other cases are invalid config
 *   - init map data
 *   - RETURN the map validation test
 * we reach the last return if we reach EOF without having all data declared
*/
int init_data(t_data *data, char **file_content)
{
  int i;
  int exit_code;

  i = 0;
  ft_bzero(data, sizeof(t_data));
  /* ft_bzero(data->colors, sizeof(datacolors)); */
  /* ft_bzero(t_textures, sizeof(data->textures)); */
  while (file_content[i])
  {
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
    exit_code = interpret_line(data, file_content[i]);
    if (exit_code < 0)
    {
      /* free_data(data); */

      return (exit_code);
    }
    i++;
    sleep (1);
    if (data->colors.ceil &&
        data->colors.floor &&
        data->textures.north &&
        data->textures.south &&
        data->textures.east &&
        data->textures.west)
    {
      while (!ft_strncmp(file_content[i], "\n", 2))
        i++;
      exit_code = get_map(data, file_content, i);
      if (exit_code != 0)
        return (exit_code);
      return (is_valid_map(data->map));
    }
  }
  return (INVALID_CONFIG);
}

int get_file_size(char *config_file)
{
  int fd;
  char *line;
  int i;

  fd = open(config_file, O_RDONLY);
  if (fd < 0)
  {
    //a virer 
    perror("open");
    return (OPEN_ERROR);
  }
  line = get_next_line(fd);
  if (!line)
  {
    close(fd);
    return (0);
  }
  i = 1;
  while (line)
  {
    free(line);
    line = get_next_line(fd);
    if (!line)
      break ;
    i++;
  }
  close(fd);
  return (i);
}

int get_file_content(char ***file_content, int fd, int size)
{
  char *line;
  int i;

  i = 0;
  *file_content = malloc(sizeof(char *) * (size + 1));
  if (!*file_content)
    return (MALLOC_ERROR);
  line = get_next_line(fd);
  if (!line && i != size)
    return (MALLOC_ERROR);
  while (line)
  {
    (*file_content)[i] = ft_strdup(line);
    if (!(*file_content)[i])
    {
      while (--i >= 0)
        free((*file_content)[i]);
      free(*file_content);
    }
    free(line);
    line = get_next_line(fd);
    i++;
    if (!line && i != size)
    {
      while (i >= 0) 
      {
        free(file_content[i]);
        i--;
      }
      free(*file_content);
      return (MALLOC_ERROR);
    }
  }
  (*file_content)[i] = NULL;
  return (0);
}

int is_valid_map_path(char *map, char ***file_content)
{
  int size;
  int fd;
  int exit_code;

  size = get_file_size(map);
  if (size == 0)
    return (FILE_EMPTY);
  if (size < 0)
    return (size);
  fd = open(map, O_RDONLY);
  if (fd < 0)
    return (OPEN_ERROR);
  exit_code = get_file_content(file_content, fd, size);
  close(fd);
  return (exit_code);
}

int parse_cub_file(char *map, t_data *data)
{
  char **file_content;
  int exit_code;

  exit_code = is_valid_map_path(map, &file_content);
  if (exit_code != 0)
    return (parsing_error_handler(data, exit_code));
  exit_code = init_data(data, file_content);
  if (exit_code != 0)
    return (parsing_error_handler(data, exit_code));
  return (0);
}
