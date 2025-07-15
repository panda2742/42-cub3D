
#include "../../include/mandatory/parse_cub_file.h"

int free_array(char **array)
{
//a recup dans la libft
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

int interpet_texture(t_data *data, char *line)
{
  if (!ft_strncmp(line, "NO", 2) && line[2] == ' ' && !data->textures.north)
  {
    data->textures.north = ft_strdup(line);
    if (!data->textures.north)
      return (MALLOC_ERROR);
    return (0);
  }
  else if (!ft_strncmp(line, "SO", 2) && line[2] == ' ' && !data->textures.south)
  {
    data->textures.south = ft_strdup(line);
    if (!data->textures.south)
      return (MALLOC_ERROR);
    return (0);
  }
  else if (!ft_strncmp(line, "WE", 2) && line[2] == ' ' && !data->textures.west)
  {
    data->textures.west = ft_strdup(line);
    if (!data->textures.west)
      return (MALLOC_ERROR);
    return (0);
  }
  else if (!ft_strncmp(line, "EA", 2) && line[2] == ' ' && !data->textures.east)
  {
    data->textures.east = ft_strdup(line);
    if (!data->textures.east)
      return (MALLOC_ERROR);
    return (0);
  }
  return (INVALID_CONFIG);
}

int is_texture_declaration(char *line)
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
      !ft_strncmp(key_value[1] + ft_strlen(key_value[1]) - 4, ".xmp", 5) &&
      access(key_value[1], F_OK | R_OK) == 0)
      exit_code = 1;
    printf("ici\n");
  }
  free_array(key_value);
  return (exit_code);
}

int init_textures(t_data *data, char **file_content, int i)
{
  int exit_code;

  while (file_content[i] && is_texture_declaration(file_content[i]) &&
  (!data->textures.north || !data->textures.south || !data->textures.west || !data->textures.east))
  {
    exit_code = interpet_texture(data, file_content[i]);
    if (exit_code < 0)
      return (exit_code);
    i++;
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
  }
  if (data->textures.north && data->textures.south && data->textures.west && data->textures.east)
    return (i);
  return (INVALID_CONFIG);
}

