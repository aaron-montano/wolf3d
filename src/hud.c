/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 05:34:05 by ytran             #+#    #+#             */
/*   Updated: 2018/09/12 05:47:58 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	*init_inventory(t_mlx *mlx)
{
	t_img	*img;
	int		i;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	if ((img->img = mlx_new_image(mlx->mlx, 64, 256)) == NULL)
		return (del_img(mlx, img));
	img->ptr = \
		mlx_get_data_addr(img->img, &img->bpp, &img->stride, &img->endian);
	img->bpp /= 8;
	img->height = 256;
	img->width = 64;
	i = 0;
	while (i < 4)
	{
		build_inv(mlx->tex[8 + i], img, 0, i * 64);
		i++;
	}
	return (img);
}

void	get_compass(t_pc *u, t_mlx *mlx)
{
	if ((u->angle <= 23 && u->angle >= 0) || (u->angle < 360 && u->angle > 338))
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- S -- SW -- |W| -- NW -- N --");
	else if (u->angle > 23 && u->angle <= 68)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- SE -- S -- |SW| -- W -- NW --");
	else if (u->angle > 68 && u->angle <= 113)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- E -- SE -- |S| -- SW -- W --");
	else if (u->angle > 113 && u->angle <= 158)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- NE -- E -- |SE| -- S -- SW --");
	else if (u->angle > 158 && u->angle <= 203)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- N -- NE -- |E| -- SE -- S --");
	else if (u->angle > 203 && u->angle <= 248)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- NW -- N -- |NE| -- E -- SE --");
	else if (u->angle > 248 && u->angle <= 293)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- W -- NW -- |N| -- NE -- E --");
	else if (u->angle > 293 && u->angle <= 338)
		mlx_string_put(mlx->mlx, mlx->win, HALF_W
				- 164, 25, 0xFFFFFF, "-- SW -- W -- |NW| -- N -- NE --");
}

void	draw_coin_count(t_mlx *mlx, t_pc *p)
{
	int		i;
	char	*n;
	char	*out;

	i = 0;
	while (i < 4)
	{
		n = ft_itoa(p->coin[i]);
		out = ft_strjoin("x", n);
		mlx_string_put(mlx->mlx, mlx->win, WIN_W
				- 42, 50 + i * 64, 0xFFFFFF, out);
		i++;
		ft_strdel(&n);
		ft_strdel(&out);
	}
}

void	draw_inventory(t_mlx *mlx)
{
	int		i;
	char	*n;
	t_pc	*p;

	p = mlx->player;
	i = 2;
	while (i < 7)
	{
		n = ft_itoa(mlx->player->held[i]);
		mlx_put_image_to_window(mlx->mlx, mlx->win,
				mlx->tex[i]->img, WIN_W - (128 * (7 - i)), WIN_H - 128);
		mlx_string_put(mlx->mlx, mlx->win,
				WIN_W - (128 * (7 - i)), WIN_H - 64, 0xFFFFFF, n);
		ft_strdel(&n);
		i++;
	}
	mlx_string_put(mlx->mlx, mlx->win,
			WIN_W - (128 * (7 - p->select)), WIN_H - 135, 0xFFFFFF, "******");
	mlx_string_put(mlx->mlx, mlx->win,
			WIN_W - (128 * (7 - p->select)), WIN_H - 75, 0xFFFFFF, "******");
	draw_coin_count(mlx, mlx->player);
}

void	draw_hud(t_mlx *mlx)
{
	char	*f;
	char	*j;
	char	*tmp;

	tmp = ft_ftoa(mlx->player->x, 3);
	f = ft_strjoin("x: ", tmp);
	mlx_string_put(mlx->mlx, mlx->win, 5, 5, 0xFFFFFF, f);
	ft_strdel(&tmp);
	tmp = ft_ftoa(mlx->player->y, 3);
	j = ft_strjoin("y: ", tmp);
	mlx_string_put(mlx->mlx, mlx->win, 5, 5, 0xFFFFFF, f);
	mlx_string_put(mlx->mlx, mlx->win, 5, 20, 0xFFFFFF, j);
	ft_strdel(&f);
	ft_strdel(&j);
	ft_strdel(&tmp);
	mlx_string_put(mlx->mlx, mlx->win, HALF_W, (HALF_H - 12), 0xFFFFFF, "+");
	get_compass(mlx->player, mlx);
	if (get_player_tile(mlx) == 9)
		mlx_string_put(mlx->mlx, mlx->win,
				HALF_W - 50, HALF_H - HALF_H / 2,
				0xFFFFFF, "Press 'T' to teleport");
}
