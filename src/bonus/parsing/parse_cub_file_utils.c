/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:23:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/23 16:30:09 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mandatory/parse_cub_file.h"

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

int	is_only_digits(char *str, char is_last)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_last == 1 && str[i] == '\n' && !str[i + 1])
			return (1);
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	free_data(t_data *data)
{
	if (!data)
		return (0);
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
	return (0);
}

int	check_data(t_data *data)
{
	if (!data->colors.ceil || !data->colors.floor || !data->textures.north
		|| !data->textures.south || !data->textures.east
		|| !data->textures.west)
		return (1);
	return (0);
}

int	parsing_error_handler(t_data *data, int exit_code)
{
	(void)data;
	write(2, "Error\n", 6);
	free_data(data);
	return (exit_code);
}
