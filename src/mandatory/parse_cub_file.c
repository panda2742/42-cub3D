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
