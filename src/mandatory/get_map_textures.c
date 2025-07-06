/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 05:23:59 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/06 05:24:02 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

bool is_a_texture_declaration(char *line)
{
  int i;

  if (!ft_strncmp(line, "NO", 2) ||
    !ft_strncmp(line,"SO", 2) ||
    !ft_strncmp(line, "WE", 2) ||
    !ft_strncmp(line, "EA", 2))
  {
    i = 0;
    while (is_space(line[i]))
      i++;
    if (is_end_of_line(line + i)) //je cherche si on a bien un NO    PATH\n
      return (true);
  }
  return (false);
}

int get_texture_path(char *line)
{
  i = 2;
  while (is_space(line[i]))
    i++;
  return (line + i);
}

int dup_texture_path(char *dest, char *line)
{
  if (dest) 
    return (1); //doublon
  dest = ft_strdup(get_texture_path(line));
  if (!dest)
  {
    return (MALLOC_ERROR);
  }
  return (0);
}

int add_texture(t_data *data, char *line)
{
  int exit_code;

  if (!ft_strncmp(file_content[i], "NO", 2) && file_content[i][2] = ' ')
    exit_code = dup_texture_path(data->textures->north, file_content[i]);
  else if (!ft_strncmp(file_content[i], "SO", 2) && file_content[i][2] = ' ')
    exit_code = dup_texture_path(data->textures->south, file_content[i]);
  else if (!ft_strncmp(file_content[i], "WE", 2) && file_content[i][2] = ' ')
    exit_code = dup_texture_path(data->textures->west, file_content[i]);
  else if (!ft_strncmp(file_content[i], "EA", 2) && file_content[i][2] = ' ')
    exit_code = dup_texture_path(data->textures->east, file_content[i]);
  if (exit_code != 0)
    return (exit_code);
  return (0);
}

int fill_textures_data(t_data *data, char ***file_content, int i)
{
  int j;

  j = 0;
  data->textures->north = NULL;
  data->textures->south = NULL;
  data->textures->west = NULL;
  data->textures->east = NULL;
  while (j < 4)
  {
    while (!ft_strncmp(file_content[i], "\n", 2))
      i++;
    if (add_texture(data, file_content[i]) != 0)
      return (1);
    j++;
    i++;
  }
  return (0);
}

bool are_textures_valid(t_data *data, char ***file_content, int i)
{
  if (!data->textures->north ||
    ft_strncmp(data->textures->north[ft_strlen(data->textures->north) - 4], ".xmp", 5) ||
    access(data->textures->north, F_OK | R_OK) != 0) //flags ok ?
    return (false);
  if (!data->textures->south ||
    ft_strncmp(data->textures->south[ft_strlen(data->textures->south) - 4], ".xmp", 5) ||
    access(data->textures->south, F_OK | R_OK) != 0) //flags ok ?
    return (false);
  if (!data->textures->west ||
    ft_strncmp(data->textures->west[ft_strlen(data->textures->west) - 4], ".xmp", 5) ||
    access(data->textures->west, F_OK | R_OK) != 0) //flags ok ?
    return (false);
  if (!data->textures->east ||
    ft_strncmp(data->textures->east[ft_strlen(data->textures->east) - 4], ".xmp", 5) ||
    access(data->textures->west, F_OK | R_OK) != 0) //flags ok ?
    return (false);
  while (file_content[i]) // si on valide toutes nos textures, on devrait pas en trouver d'autres dans le fichier
  {
    if (is_a_texture_declaration(file_content[i]))
      return (false);
    i++;
  }
  return (true);
}

bool get_textures_from_file(char ***file_content)
{
  int i;

  data->textures = NULL;
  i = 0;
  while (file_content[i])
  {
    if (is_a_texture_declaration(file_content[i]))
    {
      i = fill_textures_data(data, file_content, i);
      if (i < 0)
        return (i);
      if (!are_textures_valid(data, file_content, i))
        return (false);
      else 
        return (true);
    }
    i++;
  }
}

int get_map_textures(t_data *data, char ***file_content)
{
  char **textures;
  int exit_code;

  exit_code = get_textures_from_file(data, file_content);
  if (exit_code != 0)
  {
    return (exit_code);
  }
  if (import_textures(textures, data) != 0)
  {
    return (INVALID_CONFIG);
  }
  return (0);
}
