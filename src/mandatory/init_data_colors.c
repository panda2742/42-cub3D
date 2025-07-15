
#include "../../include/mandatory/parse_cub_file.h"

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

int get_color_code(char *line, int color_code[3])
{
  int i;
  char **splitted;

  i = 1;
  while (line[i] && line[i] == ' ')
    i++;
  splitted = ft_split(line + i, ',');
  if (!splitted)
    return (MALLOC_ERROR);
  if (splitted[0] && splitted[1] && splitted[2] && !splitted[3] &&
      is_only_digits(splitted[0]) && is_only_digits(splitted[1]) && is_only_digits(splitted[2]))
  {
    color_code[0] = ft_atoi(splitted[0]);
    color_code[1] = ft_atoi(splitted[1]);
    color_code[2] = ft_atoi(splitted[2]);
    free_array(splitted);
    if (color_code[0] < 0 || color_code[0] > 255 || 
        color_code[1] < 0 || color_code[1] > 255 ||
        color_code[2] < 0 || color_code[2] > 255)
      return (INVALID_CONFIG);
    return (0);
  }
  free_array(splitted);
  return (INVALID_CONFIG);
}

bool check_color_values(char **colors)
{
  int i;
  int n;

  i = 0;
  while (colors[i])
  {
    n = ft_atoi(colors[i]);
    if (n < 0 || n > 255)
      return (false);
    i++;
  }
  return (true);
}

int is_color_declaration(char *line)
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

int init_colors(t_data *data, char **file_content, int i)
{
  while (file_content[i] && is_color_declaration(file_content[i]) && 
    (!data->colors.ceil[0] || !data->colors.floor[0]))
  {
    if (!ft_strncmp(file_content[i], "C", 1) && file_content[i][1] == ' ' && !data->colors.ceil[0]) 
      return(get_color_code(file_content[i], data->colors.ceil));
    if (!ft_strncmp(file_content[i], "F", 1) && file_content[i][1] == ' ' && !data->colors.floor[0]) 
      return(get_color_code(file_content[i], data->colors.floor));
    else
      return (INVALID_CONFIG);
    i++;
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
  }
  return (0);
}
/* int is_map_declaration(t_data *data, char **file_content, int i, bool player) */
/* { */
/*   int j; */
/**/
/*   j = 0; */
/*   while (file_content[i][j]) */
/*   { */
/*     if (file_content[i][j] == ' ' || file_content[i][j] == '0' || file_content[i][j] == '1' || (file_content[i][j] == 'N' && player = false)) */
/*     { */
/*       if (file_content[i][j] == 'N') */
/*         player = true; */
/*     } */
/*     j++; */
/*   } */
/*   if (file_content[i][j]) */
/*     return (INVALID_CONFIG); */
/*   if (file_content[i + 1]) */
/*     return (is_map_declaration(data, file_content, i + 1, player)); */
/*   else  */
/*     return (1); */
/* } */

/* int check_player(char **map) */
/* { */
/*   int i; */
/*   int j; */
/*   bool player; */
/**/
/*   player = false; */
/*   while (map[i]) */
/*   { */
/*     while (map[i][j]) */
/*     { */
/*       if (map[i][j] == 'N') */
/*       { */
/*         if (player == true) */
/*           return (INVALID_CONFIG); */
/*         else */
/*           player = true; */
/*       } */
/*       j++; */
/*     } */
/*     i++; */
/*   } */
/*   if (player) */
/*     return (true); */
/*   return (false); */
/* } */
/**/
