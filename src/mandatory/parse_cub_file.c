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

int free_array(char **array)
{
  int i;

  i = 0;
  while (array[i])
  {
    free(array[i]);
    i++;
  }
  free(array);
  return (0);
}

int free_data(t_data *data)
{
  if (data->textures.north)
    free(data->textures.north);
  if (data->textures.south)
    free(data->textures.south);
  if (data->textures.west)
    free(data->textures.west);
  if (data->textures.east)
    free(data->textures.east);
  if (data->colors.ceil)
    free(data->colors.ceil);
  if (data->colors.floor)
    free(data->colors.floor);
  if (data->map)
    free_array(data->map);
  return (0);
}

int parsing_error_handler(t_data *data, int exit_code)
{
  (void)data;
  printf("Error\n");
  free_data(data);
  return (exit_code);
}

int load_texture(char **slot, char **key_value)
{
  *slot = ft_strdup(key_value[1]);
  if (!*slot)
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
    return (load_texture(&data->textures.north, key_value));
  if (!ft_strncmp(key_value[0], "SO", 3) && !data->textures.south)
    return (load_texture(&data->textures.south, key_value));
  if (!ft_strncmp(key_value[0], "WE", 3) && !data->textures.west)
    return (load_texture(&data->textures.west, key_value));
  if (!ft_strncmp(key_value[0], "EA", 3) && !data->textures.east)
    return (load_texture(&data->textures.east, key_value));
  return (INVALID_CONFIG);
}

int load_color(int **slot, char **color_code, char **key_value)
{
  *slot = malloc(sizeof(int) * 3);
  if (!*slot)
  {
    free_array(color_code);
    free_array(key_value);
    return (MALLOC_ERROR);
  }
  (*slot)[0] = ft_atoi(color_code[0]);
  (*slot)[1] = ft_atoi(color_code[1]);
  (*slot)[2] = ft_atoi(color_code[2]);
  free_array(color_code);
  free_array(key_value);
  if ((*slot)[0] < 0 || (*slot)[0] > 255 || 
      (*slot)[1] < 0 || (*slot)[1] > 255 ||
      (*slot)[2] < 0 || (*slot)[2] > 255)
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
      return (load_color(&data->colors.ceil, color_code, key_value));
    if (!ft_strncmp(key_value[0], "F", 2) && !data->colors.floor)
      return (load_color(&data->colors.floor, color_code, key_value));
  }
  return (INVALID_CONFIG);
}

int interpret_line(t_data *data, char *line)
{
  char **key_value;
  char **color_code;

  /* printf("line = %s\n", line); */
  line[ft_strlen(line) - 1] = '\0';
  key_value = ft_split(line, ' ');
  if (!key_value)
    return (MALLOC_ERROR);
  if (key_value[0] && key_value[1] && !key_value[2])
  {
    if (ft_strlen(key_value[0]) == 2 && ft_strlen(key_value[1]) >= 4 &&
      !ft_strncmp(key_value[1] + ft_strlen(key_value[1]) - 4, ".xmp", 5))
      return (interpret_texture(data, key_value));
    else if (ft_strlen(key_value[0]) == 1)
    {
      color_code = ft_split(key_value[1], ',');
      if (!color_code)
      {
        free_array(key_value);
        return (MALLOC_ERROR);
      }
      return (interpret_color(data, key_value, color_code));
    }
  }
  /* printf("key = %s | value = %s\n", key_value[0], key_value[1]); */
  return (INVALID_CONFIG);
}

int check_data(t_data *data)
{
  if (!data->colors.ceil ||
        !data->colors.floor ||
        !data->textures.north ||
        !data->textures.south ||
        !data->textures.east ||
        !data->textures.west)
    return (1);
  return (0);
}

/* int print_load(t_data *data) */
/* { */
/*   if (data->textures.north) */
/*     printf("data->textures.north = %s\n", data->textures.north); */
/*   if (data->textures.south) */
/*     printf("data->textures.south = %s\n", data->textures.south); */
/*   if (data->textures.west) */
/*     printf("data->textures.west = %s\n", data->textures.west); */
/*   if (data->textures.east) */
/*     printf("data->textures.east = %s\n", data->textures.east); */
/*   if (data->colors.ceil) */
/*     printf("data->colors.ceil = %d %d %d\n", data->colors.ceil[0], data->colors.ceil[1], data->colors.ceil[2]); */
/*   if (data->colors.floor) */
/*     printf("data->colors.floor = %d %d %d\n", data->colors.floor[0], data->colors.floor[1], data->colors.floor[2]); */
/*   return (0); */
/* } */

/* for each line of the config file AND as long as data fields are not fill : 
 * - skip \n
 * - check if the line is a valid declaration
 *   - load matching field if valid config line
 *   - return error if invalid config line
 * 
 * When we reached EOF or when all data fields are fill :
 * - skip \n
 * - we can assme we are either on the first line of the map, or it's an invalid config
 *   - load map in a buffer
 * - final check if the map is valid as return value
*/
int init_data(t_data *data, char **file_content)
{
  int i;
  int exit_code;

  i = 0;
  ft_bzero(data, sizeof(t_data));
  /* ft_bzero(data->colors, sizeof(datacolors)); */
  /* ft_bzero(t_textures, sizeof(data->textures)); */
  while (file_content[i] && check_data(data))
  {
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
    exit_code = interpret_line(data, file_content[i]);
    if (exit_code < 0)
    {
      free_data(data);
      return (exit_code);
    }
    /* print_load(data); */
    i++;
  }
  while (!ft_strncmp(file_content[i], "\n", 2))
    i++;
  exit_code = get_map(data, file_content, i);
  if (exit_code != 0)
  {
    free_data(data);
    return (exit_code);
  }
  return (is_valid_map(data->map));
  /* return (INVALID_CONFIG); */
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
  free_array(file_content);
  if (exit_code != 0)
    return (parsing_error_handler(data, exit_code));
  return (0);
}
