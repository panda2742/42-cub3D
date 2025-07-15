
#include "../../include/mandatory/parse_cub_file.h"

 /* for each char of each line : 
  * if it's not ' ' 0 1 NSEW : INVALID_CONFIG 
  * if we find two P : INVALID_CONFIG
  * */
int is_valid_map_format(char **map)
{
  int i;
  int j;
  bool player;

  player = false;
  i = 0;
  j = 0;
  while (map[i])
  {
    j = 0;
    while (map[i][j])
    {
      if (map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != '1' &&
        map[i][j] != 'N' &&
        map[i][j] != 'E' &&
        map[i][j] != 'W' &&
        map[i][j] != 'S')
        return (INVALID_CONFIG);
      //add parenthesis ?
      if ((map[i][j] == 'N' || 
        map[i][j] == 'S' ||
        map[i][j] == 'E' ||
        map[i][j] == 'W') && 
        player == true)
        return (INVALID_CONFIG);
      else
        player = true;
      j++;
    }
    i++;
  }
  return (0);
}
/**/
/* int is_valid_map(char **map) */
/* { */
/*   if (!check_player(map) || !check_closed_map(map)) */
/*     return (INVALID_CONFIG); */
/*   else */
/*     return (1); */
/* } */

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
  data->map = malloc(sizeof(char *) * get_map_size(file_content, i) + 1);
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

/*
 * 2 is the wall we are testing
 * 3 is a wall already tested as closed
 * 1 is a new wall not tested
 *
 * recursive function : called first time on the first wall found
 * if we found arround the wall we are testing or an already closed wall : we consider the wall as closed
 *  - we mark as 3 each wall on the path of the recursive
 *
 * if we dont find a wall arround : error
 * */
int is_wall_closed(char **map, int i, int j)
{
  int exit_code;

  if ((map[i][j - 1] && map[i][j - 1] <= '2') ||
      (map[i][j + 1] && map[i][j + 1] <= '2') || 
      (map[i + 1][j] && map[i + 1][j] <= '2') ||
      (map[i - 1][j] && map[i - 1][j] <= '2'))
  {
    map[i][j] = '3';
    return (1);
  }
  if ((map[i][j - 1] && map[i][j - 1] == '1') ||
      (map[i][j + 1] && map[i][j + 1] == '1') || 
      (map[i + 1][j] && map[i + 1][j] == '1') ||
      (map[i - 1][j] && map[i - 1][j] == '1'))
  {
    map[i][j] = '2';
    exit_code = is_wall_closed(map, i, j);
    if (exit_code == 1)
    {
      map[i][j] = '3';
      return (1);
    }
    else if (exit_code == 2)
      return (INVALID_CONFIG);
  }
  return (2);
}

int check_wall(char **map, int i)
{
  int j;

  j = 0;
  while (map[i][j])
  {
    while (map[i][j] == ' ' || map[i][j] == '0' || map[i][j] == '2' || 
      map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
      j++;
    if (map[i][j] == '1' && !is_wall_closed(map, i, j))
      return (INVALID_CONFIG);
    j++;
  }
  return (0);
}

int are_wall_closed(char **map)
{
  int i;

  i = 0;
  while (map[i])
  {
    if (check_wall(map, i))
      return (INVALID_CONFIG);
    i++;
  }
  return (0);
}

/*
 * We check first is all chars in map are valid (0 1 ' ' or P)
 *    in same time : if there is only one P in the map
 * then if all walls are correctly closed 
 * */
int is_valid_map(char **map)
{
  if (is_valid_map_format(map))
    return (INVALID_CONFIG);
  return (are_wall_closed(map));
  //un check en plus pour savoir si le joueur est bien enferme dans des murs ?
}
