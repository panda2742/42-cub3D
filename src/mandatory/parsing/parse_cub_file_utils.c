/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:23:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/19 17:21:33 by oelleaum         ###   ########lyon.fr   */
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

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
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
	if (data->map.grid)
		free_array(data->map.grid);
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
	write(2, "Error\n", 6); //a mettre sur la stderr
	free_data(data);
	return (exit_code);
}
