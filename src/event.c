/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 03:11:19 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 01:17:39 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_vec	find_warp_zone(t_map *dest)
{
	t_vec	ret;
	t_tile	*t;
	int		y;
	int		x;

	ret.x = 0;
	ret.y = 0;
	ret.dir = 0;
	y = -1;
	while (++y < dest->h)
	{
		x = -1;
		while (++x < dest->w)
			if (get_tile(dest, x, y) == 8)
			{
				ret.a = x;
				ret.b = y;
				return (ret);
			}
	}
	t = first_empty_tile(dest);
	ret.a = t->x;
	ret.b = t->y;
	return (ret);
}

void			change_zone(t_mlx *mlx, t_map *dest)
{
	t_vec	spawn;
	t_pc	*tmp;

	tmp = mlx->player;
	spawn = find_warp_zone(dest);
	mlx->map = dest;
	tmp->x = spawn.a + 0.5;
	tmp->y = spawn.b + 0.5;
	mlx->player = tmp;
	get_music(mlx);
	system("afplay -v 2 sounds/smw_pipe.wav &");
	draw_bg(mlx, -1, -1);
}

void			pickup(t_mlx *mlx, t_map *map)
{
	int		y;
	int		x;
	int		p;

	y = (int)floor(mlx->player->y + mlx->player->diry);
	x = (int)floor(mlx->player->x + mlx->player->dirx);
	p = map->grid[y][x]->properties;
	if (p != 1 && p != 9 && p != 0 && p < TEX_SZ && p > 0)
	{
		if (p < TEX_SZ && mlx->player->held[p] < 99)
		{
			map->grid[y][x]->properties = 0;
			mlx->player->held[p] += 1;
			system("afplay -v 2 sounds/smw_break_block.wav &");
		}
	}
}

void			drop(t_mlx *mlx, t_map *map)
{
	int		y;
	int		x;
	int		p;
	t_pc	*pc;

	pc = mlx->player;
	y = (int)floor(mlx->player->y + mlx->player->diry);
	x = (int)floor(mlx->player->x + mlx->player->dirx);
	p = map->grid[y][x]->properties;
	if (mlx->player->held[pc->select] > 0 && p == 0)
	{
		map->grid[y][x]->properties = pc->select;
		mlx->player->held[pc->select] -= 1;
		system("afplay -v 2 sounds/smw_fireball.wav &");
	}
}

void			scan_event(t_mlx *mlx)
{
	int		e;
	int		id;

	id = mlx->map->id;
	e = get_player_tile(mlx);
	if (e == 9)
	{
		if (mlx->all_maps[id + 1] != NULL)
			change_zone(mlx, mlx->all_maps[id + 1]);
		else
			change_zone(mlx, mlx->all_maps[0]);
	}
}
