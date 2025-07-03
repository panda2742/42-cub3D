/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_getline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:14:17 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/03 12:40:48 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char*	_get_cleaned(char* line, const char* ign_set, size_t cleaned_len, t_errors_container* errc);

char*	clean_getline(int fd, const char* ign_set, t_errors_container* errc)
{
	char*	line;
	size_t	line_len;
	size_t	cleaned_len;

	line = get_next_line(fd);
	if (line == NULL)
	{
		errc->cannot_open = 1;
		return (NULL);
	}
	cleaned_len = 0;
	line_len = -1;
	while (line[++line_len])
	{
		if (ft_isincharset(line[line_len], ign_set))
			continue;
		cleaned_len++;
	}
	printf("Size: %zu\n", cleaned_len);
	return (_get_cleaned(line, ign_set, cleaned_len, errc));
}

static char*	_get_cleaned(char* line, const char* ign_set, size_t cleaned_len, t_errors_container* errc)
{
	char*	res;
	size_t	i;
	size_t	j;

	res = malloc((cleaned_len + 1) * sizeof(char));
	res[cleaned_len] = 0;
	if (res == NULL)
	{
		errc->malloc_err = 1;
		return (NULL);
	}
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (ft_isincharset(line[i], ign_set))
			continue;
		res[j++] = line[i];
	}
	free(line);
	return (res);
}
