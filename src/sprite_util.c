/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 23:59:15 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 00:03:23 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sort_sprites_by_dist(int *order, double *dist, int n)
{
	int	gap;
	int	swapped;
	int	i;
	int	k;

	swapped = 0;
	gap = n;
	while (gap > 1 || swapped)
	{
		i = -1;
		gap = (gap * 10) / 13;
		gap = (gap == 9 || gap == 10) ? 11 : gap;
		gap = (gap < 1) ? 1 : gap;
		swapped = 0;
		while (++i < n - 1)
		{
			k = i + gap;
			if (dist[i] < dist[k])
			{
				ft_swap_d(&dist[k], &dist[i]);
				ft_swap(&order[k], &order[i]);
				swapped = 1;
			}
		}
	}
}

void	update_coin(t_pc *p, char c)
{
	if (c == 'C')
		p->coin[0] += 1;
	else if (c == 'Y')
		p->coin[1] += 1;
	else if (c == 'R')
		p->coin[2] += 1;
	else if (c == 'T')
		p->coin[3] += 1;
	else if (c == 'F')
		p->wincondition += 1;
}

int		get_sound(t_pc *p, char c)
{
	update_coin(p, c);
	if (c == 'C')
		system("afplay -v 3 sounds/smw_coin.wav &");
	else if (c == 'Y')
		system("afplay -v 1 sounds/smw_dragon_coin.wav &");
	else if (c == 'R')
		system("afplay -v 1 sounds/oot_rupee.wav &");
	else if (c == 'T')
		system("afplay -v 1 sounds/oot_fanfare.wav &");
	else if (c == 'F')
		system("afplay -v 1 sounds/oot_hc.wav &");
	else
		return (0);
	return (1);
}

void	sprite_collision(int aa, double *dist, int *order, t_mlx *mlx)
{
	char	c;
	int		y;
	int		x;

	x = (int)(mlx->sprites[order[aa]]->x);
	y = (int)(mlx->sprites[order[aa]]->y);
	if (mlx->sprites[order[aa]] &&
			(mlx->sprites[order[aa]]->map == mlx->map) && (dist[aa] < 0.25))
	{
		c = mlx->map->grid[y][x]->sprite;
		if (get_sound(mlx->player, c))
			mlx->sprites[order[aa]]->map = NULL;
	}
}
