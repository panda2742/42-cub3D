/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:47:23 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 12:43:02 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parsing_result	parse_map(const char* map_filename)
{
	t_parsing_result 	res;
	int					fd;
	char*				test_line;

	res.val = 0;
	fd = open_file(map_filename, &res.flags);
	while (1)
	{
		test_line = clean_getline(fd, " \t\r\v", &res.flags);
		printf("Cleaned line: %s", test_line);
		if (test_line == NULL)
			break ;
		free(test_line);
	}
	return (res);
}