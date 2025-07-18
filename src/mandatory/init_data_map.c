
#include "../../include/mandatory/parse_cub_file.h"

int get_map_size(char **file_content, int i)
{
  int j;

  j = i;
  while (file_content[j])
    j++;
  return (j - i);
}

int get_map(t_data *data, char **file_content, int i)
{
  int j;

  j = 0;
  data->map = malloc(sizeof(char *) * (get_map_size(file_content, i) + 1));
  if (!data->map)
    return (MALLOC_ERROR);
  while (file_content[i])
  {
    data->map[j] = ft_strdup(file_content[i]);
    if (!data->map[j])
    {
      while (j - 1 >= 0)
      {
        free(data->map[j - 1]);
        j--;
      }
      return (MALLOC_ERROR);
    }
    j++;
    i++;
  }
  data->map[j] = NULL; 
  return (0);
}

/* if a '0' or the player is 
 *  - adjacent to a space, or
 *  - on the edge of the ma :
 * the map can't be surrounded by wall : invalid configuration */
int check_wall(char **map, int i, int size)
{
  int j;

  j = 0;
  while (map[i][j])
  {
    if (map[i][j] == '0' || 
      map[i][j] == 'N' ||
      map[i][j] == 'S' ||
      map[i][j] == 'W' ||
      map[i][j] == 'E')
    {
      if (i == 0 || i == size ||
     j == 0 || map[i][j + 1] == '\n')
        return (INVALID_CONFIG);
      if ((map[i][j - 1] && map[i][j - 1] == ' ') ||
          (map[i][j + 1] && map[i][j + 1] == ' ') ||
          (map[i - 1][j] && map[i - 1][j] == ' ') ||
          (map[i + 1][j] && map[i + 1][j] == ' '))
        return (INVALID_CONFIG);
    }
    j++;
  }
  return (0);
}

/* for each line of the map ... */
int are_wall_closed(char **map, int size)
{
  int i;

  i = 0;
  while (map[i])
  {
    if (check_wall(map, i, size))
      return (INVALID_CONFIG);
    i++;
  }
  return (0);
}

/*
 * We check first if all chars in map are valid (0 1 ' ' or N/S/E/W)
 *    in same time : if there is only one player on the map
 * then if walls are correctly closed 
 * */
//
//un check en plus pour savoir si le joueur est bien enferme dans des murs ?
//
int is_valid_map(char **map)
{
  int size;

  size = 0;
  while (map[size])
    size++;
  if (is_valid_map_format(map))
    return (INVALID_CONFIG);
  return (are_wall_closed(map, size));
}
