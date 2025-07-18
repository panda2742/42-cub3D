
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

int parsing_error_handler(t_data *data, int exit_code)
{
  (void)data;
  printf("Error\n");
  free_data(data);
  return (exit_code);
}
