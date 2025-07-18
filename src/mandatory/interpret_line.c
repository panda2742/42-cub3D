
//header missing
//doc ?
//to format

#include "../../include/mandatory/parse_cub_file.h"

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
  return (INVALID_CONFIG);
}
