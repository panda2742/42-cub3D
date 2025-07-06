/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:59:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/06 03:00:20 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int parsing_error_handler(char *map, t_data *data)
{
  printf("Error\n");
  //free ici
  return (1);
}

int get_file_content(char *map, char ***file_content, int fd, int size)
{
  int i;
  char *line;
  int exit_code;

  file_content = malloc(sizeof(char **) * size + 1);
  if (!file_content)
  {
    //free ici
    return (MALLOC_ERROR);
  }
  //je dois le reopen pour reparser avec gnl ?
  file_content[0] = get_next_line(fd);
  if (!file_content[0])
  {
    //free ici
    return (MALLOC_ERROR);
  }
  i = 1;
  while (i < size)
  { 
    i++;
    file_content[i] = get_next_line(fd);
  }
  i++;
  file_content[i] = NULL;
  return (0);
}

int is_valid_file(char *map)
{
  int fd;

  if (access(map, F_OK | R_OK) == 0)
  {
    fd = open(map, O_RDONLY);
    if (fd == -1)
    {
      return (OPEN_ERROR); // negative
    }
  }
  else 
  {
    //l'access a rate
    return (ACCESS_ERROR); //negative
  }
  return (fd);
}

int get_file_size(char *map, int fd)
{
  int i;
  char *line;

  i = 0;
  line = get_next_line(fd);
  while(line)
  {
    i++;
    free(line);
    line = get_next_line(fd);
  }
  return (i);
}

int is_valid_map_path(char *map, char ***file_content)
{
  int fd;
  int size;
  int exit_code;

  fd = is_valid_file(map);
  if (fd < 0)
    return (fd);
  size = get_file_size(map);
  if (size == 0)
  {
    //file empty
    return (FILE_EMPTY);
  }
  exit_code = get_file_content(map, file_content, fd, size);
  if (exit_code)
    return (exit_code);
}
