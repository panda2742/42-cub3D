/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:00:52 by ehosta            #+#    #+#             */
/*   Updated: 2025/07/23 13:35:42 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_bonus.h"

static inline char	_get_tile(t_ivec2 pos, t_gdata *gdata)
					__attribute__((always_inline));
static inline void	_door_interact(const t_ivec2 tile_pos[4], char tiles[4],
						double dists[4], t_gdata *game)
					__attribute__((always_inline));
static inline void	_change_tile(char tile, t_ivec2 pos, t_gdata *game)
					__attribute__((always_inline));

void	door_interact(t_render *render)
{
	const t_ivec2	map = {
		.x = (int)render->game.pos.x,
		.y = (int)render->game.pos.y,
	};
	const t_ivec2	tile_pos[4] = {
	{.x = map.x, .y = map.y - 1},
	{.x = map.x - 1, .y = map.y},
	{.x = map.x, .y = map.y + 1},
	{.x = map.x + 1, .y = map.y}
	};
	size_t			i;
	char			tiles[4];
	double			dists[4];

	i = -1;
	while (++i < 4)
	{
		tiles[i] = _get_tile(tile_pos[i], &render->game);
		if (tiles[i] == 'P' || tiles[i] == 'T')
			dists[i] = sqrt(pow(tile_pos[i].x - render->game.pos.x, 2)
					+ pow(tile_pos[i].y - render->game.pos.y, 2));
	}
	_door_interact(tile_pos, tiles, dists, &render->game);
}

static __attribute__((always_inline))
inline char	_get_tile(t_ivec2 pos, t_gdata *gdata)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= (int)gdata->map.height
		|| pos.x >= (int)gdata->map.lengths[pos.y])
		return (0);
	return (gdata->map.data[pos.y][pos.x]);
}

static __attribute__((always_inline))
inline void	_door_interact(const t_ivec2 tile_pos[4], char tiles[4],
				double dists[4], t_gdata *game)
{
	char	valid[4];
	size_t	i;
	size_t	closest;

	i = -1;
	while (++i < 4)
		valid[i] = tiles[i] == 'T' || tiles[i] == 'D';
	closest = 0;
	while (!valid[closest] && closest < 4)
		closest++;
	if (closest == 4 && !valid[closest - 1])
		return ;
	i = closest;
	while (++i < 4)
	{
		if (!valid[i])
			continue ;
		if (dists[i] < dists[closest])
			closest = i;
	}
	_change_tile(tiles[closest], tile_pos[closest], game);
}

static __attribute__((always_inline))
inline void	_change_tile(char tile, t_ivec2 pos, t_gdata *game)
{
	if (tile == 'D')
		game->map.data[pos.y][pos.x] = 'T';
	if (tile == 'T')
		game->map.data[pos.y][pos.x] = 'D';
}
