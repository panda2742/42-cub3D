
#include "../../include/mandatory/parse_cub_file.h"

static int is_valid_char(char c)
{
  if (c != ' ' && c != '0' && c != '1' &&
    c != 'N' &&
    c != 'E' &&
    c != 'W' &&
    c != 'S')
    return  (INVALID_CONFIG);
  return (0);
}

static int is_player_char(char c, bool *player)
{
  if (c == 'N' || 
    c == 'S' ||
    c == 'E' ||
    c == 'W')
  {
    if (*player == true)
      return ( INVALID_CONFIG);
    *player = true;
  }
  return (0);
}

 /* for each char of each line : 
  * if it's not ' ' 0 1 NSEW : INVALID_CONFIG 
  * if we find two players : INVALID_CONFIG
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
      if (map[i][j] == '\n')
        break ;
      if (is_valid_char(map[i][j]) < 0)
        return (INVALID_CONFIG);
      if (is_player_char(map[i][j], &player) < 0)
      j++;
    }
    i++;
  }
  return (0);
}



