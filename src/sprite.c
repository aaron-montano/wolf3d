/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 01:05:12 by ytran             #+#    #+#             */
/*   Updated: 2018/09/14 00:02:48 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		get_sprite_dist(int *order, double *dist, t_mlx *mlx, t_pc *p)
{
	int		aa;
	double	tx;
	double	ty;

	aa = 0;
	while (aa < mlx->n_sprites)
	{
		order[aa] = aa;
		tx = p->x - mlx->sprites[aa]->x;
		ty = p->y - mlx->sprites[aa]->y;
		dist[aa] = (tx * tx) + (ty * ty);
		dist[aa] = sqrt(dist[aa]);
		aa++;
	}
}

/*
** 0 = screenx;
** 1 = sprite_width;
** 2 = sprite_height
** 3 = y-drawstart;
** 4 = y-drawend;
** 5 = x-drawstart;
** 6 = x-drawend;
** 7 = aa;
*/

void		get_sprite_data(double depth, int screenx, int *sd)
{
	sd[0] = screenx;
	sd[1] = (int)floor(fabs(WIN_H / depth));
	sd[2] = (int)floor(fabs(WIN_H / depth));
	sd[3] = -sd[2] / 2 + HALF_H;
	sd[3] = (sd[3] < 0) ? 0 : sd[3];
	sd[4] = sd[2] / 2 + HALF_H;
	sd[4] = (sd[4] >= WIN_H) ? WIN_H - 1 : sd[4];
	sd[5] = -sd[1] / 2 + screenx;
	sd[5] = (sd[5] < 0) ? 0 : sd[5];
	sd[6] = sd[1] / 2 + screenx;
	sd[6] = (sd[6] >= WIN_W) ? WIN_W - 1 : sd[6];
}

t_vec		project_sprites(t_mlx *mlx, t_pc *p, int *order, int aa)
{
	double	spx;
	double	spy;
	double	inv;
	double	newx;
	t_vec	uv;

	spx = mlx->sprites[order[aa]]->x - p->x;
	spy = mlx->sprites[order[aa]]->y - p->y;
	inv = 1.0 / ((p->camx * p->diry) - (p->dirx * p->camy));
	newx = inv * (p->diry * spx - p->dirx * spy);
	uv.y = inv * (-(p->camy) * spx + p->camx * spy);
	uv.a = (int)floor((double)HALF_W * (1.0 + newx / uv.y));
	uv.x = 0;
	uv.b = 0;
	uv.dir = 0;
	return (uv);
}

void		draw_sprite_tex(int *sd, t_vec uv, t_mlx *mlx, int *o)
{
	int i;
	int k;
	int x;
	int y;
	int color;

	i = sd[5];
	while (i < sd[6])
	{
		x = (256 * (i - (-sd[1] / 2 + sd[0])) * TEX_W / sd[1]) >> 8;
		if (uv.y > 0 && i > 0 && (i < WIN_W) && (uv.y < mlx->zbuf[i]))
		{
			k = sd[3];
			while (k < sd[4])
			{
				y = (((k << 8) - (WIN_H << 7) + (sd[2] << 7)) * TEX_W / sd[2]) \
					>> 8;
				color = grab_color_from_tex(x, y, mlx->sprites[o[sd[7]]]->tex);
				if (color != 0x9C27B0)
					img_set_pixel(mlx->img, i, k, color);
				k++;
			}
		}
		i++;
	}
}

void		draw_sprites(t_mlx *mlx, t_pc *p, int total)
{
	int					order[total];
	double				dist[total];
	int					aa;
	int					sd[8];
	t_vec				uv;

	get_sprite_dist(order, dist, mlx, p);
	sort_sprites_by_dist(order, dist, mlx->n_sprites);
	aa = 0;
	while (aa < total)
	{
		if (order[aa] < mlx->n_sprites &&
				mlx->sprites[order[aa]]->map == mlx->map && dist[aa])
		{
			sprite_collision(aa, dist, order, mlx);
			uv = project_sprites(mlx, p, order, aa);
			get_sprite_data(uv.y, uv.a, sd);
			sd[7] = aa;
			draw_sprite_tex(sd, uv, mlx, order);
		}
		aa++;
	}
}
