/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 19:02:06 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 06:10:34 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_tile			*first_empty_tile(t_map *map)
{
	int		i;
	int		k;
	t_tile	*t;

	i = 0;
	while (i < map->h)
	{
		k = 0;
		while (k < map->w)
		{
			t = map->grid[i][k];
			if (!t->properties && !t->sprite)
				return (map->grid[i][k]);
			k++;
		}
		i++;
	}
	return (NULL);
}

static void		init_player_properties(t_pc *p, t_mlx *mlx)
{
	t_tile	*t;

	if ((t = first_empty_tile(mlx->map)) != NULL)
	{
		p->x = (double)t->x + 0.5;
		p->y = (double)t->y + 0.5;
	}
	p->dirx = -1;
	p->diry = 0;
	p->camx = 0;
	p->camy = 0.66;
	p->angle = 0;
	rotate(p, 1, M_PI_2 * 3);
}

static void		init_player_inventory(t_pc *p)
{
	int	i;

	i = 0;
	p->wincondition = 0;
	p->select = 2;
	while (i < TEX_SZ)
	{
		if (i < 4)
			p->coin[i] = 0;
		p->held[i] = 0;
		i++;
	}
}

t_pc			*init_player(t_mlx *mlx)
{
	t_pc	*p;

	if (!(p = (t_pc *)malloc(sizeof(t_pc))))
		return (NULL);
	init_player_properties(p, mlx);
	init_player_inventory(p);
	return (p);
}

int				get_player_tile(t_mlx *mlx)
{
	return (get_tile(mlx->map, mlx->player->x, mlx->player->y));
}
