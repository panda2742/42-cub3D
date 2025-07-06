/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:18:59 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/06 05:23:55 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cub_file.h"



int parse_cub_file(char *map, t_data *data)
{
  char **file_content;

  if (is_valid_map_path(map, &file_content))
    return (parsing_error_handler(data, &file_content));
  if (get_map_textures(data))
    return (parsing_error_handler(data));
  if (get_colors_(data))
    return (parsing_error_handler(data));
  if (get_map(data))
    return (parsing_error_handler(data));
  return (0);
}
