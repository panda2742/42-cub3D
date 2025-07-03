/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:43:40 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 17:36:39 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_config*	create_map_config(void)
{
	t_map_config*	res;

	res = malloc(sizeof(t_map_config));
	if (res == NULL)
		return (NULL);
	res->no_texture_name = NULL;
	res->so_texture_name = NULL;
	res->we_texture_name = NULL;
	res->ea_texture_name = NULL;
	res->floor_color = NULL;
	res->ceiling_color = NULL;
	return (res);
}
