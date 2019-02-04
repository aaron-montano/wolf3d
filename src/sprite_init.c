/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 04:12:00 by amontano          #+#    #+#             */
/*   Updated: 2018/09/18 19:22:45 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			count_sprites(t_map **world)
{
	int		i;
	int		k;
	t_map	*cur;
	int		count;
	int		w;

	count = 0;
	w = 0;
	while (w < N_MAPS)
	{
		cur = world[w];
		i = -1;
		while (++i < cur->h)
		{
			k = -1;
			while (++k < cur->w)
				if (cur->grid[i][k]->sprite != '\0')
					count++;
		}
		w++;
	}
	return (count);
}

void		assign_texture(char c, t_sprite *s, t_mlx *mlx)
{
	if (c == 'E')
		s->tex = mlx->tex[7];
	if (c == 'C')
		s->tex = mlx->tex[8];
	if (c == 'Y')
		s->tex = mlx->tex[9];
	if (c == 'R')
		s->tex = mlx->tex[10];
	if (c == 'T')
		s->tex = mlx->tex[11];
	if (c == 'F')
		s->tex = mlx->tex[12];
}

t_sprite	*create_sprite(double x, double y, t_map *map)
{
	t_sprite	*new_sprite;

	if (!(new_sprite = (t_sprite *)malloc(sizeof(t_sprite))))
	{	
		while (1);	
		return (NULL);
	}
	new_sprite->map = map;
	new_sprite->x = x;
	new_sprite->y = y;
	return (new_sprite);
}

int			sprites_on_map(t_mlx *mlx, int n, t_sprite **all, int w)
{
	int		i;
	int		k;
	char	c;

	i = -1;
	while (++i < mlx->all_maps[w]->h)
	{
		k = -1;
		while ((++k < mlx->all_maps[w]->w) && (n < mlx->n_sprites))
		{
			if ((c = mlx->all_maps[w]->grid[i][k]->sprite))
			{
				if ((all[n] = create_sprite(k + 0.5,
								i + 0.5, mlx->all_maps[w])) == NULL)
					return (-1);
				assign_texture(c, all[n], mlx);
				n++;
			}
		}
	}
	return (n);
}

t_sprite	**init_sprites(t_mlx *mlx)
{
	int			n;
	int			w;
	t_sprite	**all;

	n = 0;
	w = 0;
	mlx->n_sprites = count_sprites(mlx->all_maps);
	if (mlx->n_sprites >= 43)
	{
		ft_putendl("too many sprites");
		return (NULL);
	}
	if (!(all = (t_sprite **)malloc(sizeof(t_sprite *) * mlx->n_sprites)))
		return (NULL);
	while (w < N_MAPS)
	{
		n = sprites_on_map(mlx, n, all, w);
		if (n == -1)
			return (NULL);
		w++;
	}
	return (all);
}
