/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 02:03:05 by ytran             #+#    #+#             */
/*   Updated: 2018/09/13 02:04:01 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		checkmap(t_map *m)
{
	if (is_full_map(m) || !is_enclosed_map(m))
	{
		system("pkill afplay");
		exit(0);
	}
	else
		return (0);
}

int		is_full_map(t_map *m)
{
	int x;
	int y;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (get_tile(m, x, y) == 0 && m->grid[y][x]->sprite == '\0')
				return (0);
			x++;
		}
		y++;
	}
	ft_putendl("map is full");
	return (1);
}

int		is_enclosed_map(t_map *m)
{
	int x;
	int y;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if ((x == 0 || y == 0 || x == m->w - 1 || y == m->h - 1) &&
					get_tile(m, x, y) != 1)
			{
				ft_putendl("map is not enclosed");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
