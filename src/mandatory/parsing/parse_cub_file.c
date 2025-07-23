/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:18:59 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/19 15:23:33 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/parse_cub_file.h"

int	skip_newlines(char **file_content, int i)
{
	while (file_content[i] && !ft_strncmp(file_content[i], "\n", 2))
		i++;
	return (i);
}

int	parse_file_content(t_data *data, char **file_content, int *i)
{
	int		exit_code;
	char	**key_value;
	char	**color_code;

	color_code = NULL;
	while (file_content[*i] && check_data(data))
	{
		while (!ft_strncmp(file_content[*i], "\n", 2))
			(*i)++;
		key_value = ft_split(file_content[*i], ' ');
		if (!key_value)
			return (MALLOC_ERROR);
		*i = skip_newlines(file_content, *i);
		if (!file_content[*i])
			break ;
		file_content[*i][ft_strlen(file_content[*i]) - 1] = '\0';
		exit_code = interpret_line(data, key_value, color_code);
		if (exit_code < 0)
			return (exit_code);
		(*i)++;
	}
	return (0);
}

int	init_data(t_data *data, char **file_content)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = parse_file_content(data, file_content, &i);
	if (exit_code < 0)
		return (exit_code);
	i = skip_newlines(file_content, i);
	exit_code = get_map(data, file_content, i);
	if (exit_code != 0)
	{
		free_data(data);
		return (exit_code);
	}
	return (is_valid_map(data));
}

int	parse_cub_file(char *map, t_data *data)
{
	char	**file_content;
	int		exit_code;

	exit_code = is_valid_map_path(map, &file_content);
	if (exit_code != 0)
		return (parsing_error_handler(data, exit_code));
	exit_code = init_data(data, file_content);
	free_array(file_content);
	if (exit_code != 0)
		return (parsing_error_handler(data, exit_code));
	return (0);
}
