/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:13:28 by amontano          #+#    #+#             */
/*   Updated: 2018/09/13 01:58:23 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "ft_color.h"

double			d_lerp(double min, double max, double pct)
{
	if (pct == 0.0)
		return (min);
	if (pct == 1.0)
		return (max);
	return ((1.0 - pct) * min + (pct * max));
}

static t_hsv	get_bg(t_mlx *mlx, char t)
{
	t_hsv	c;

	if (mlx->map == mlx->all_maps[0])
	{
		if (t == 'g')
			c = (t_hsv){120.0, 0.32, 0.5};
		if (t == 's')
			c = (t_hsv){240.0, 0.5, 0.25};
	}
	if (mlx->map == mlx->all_maps[1])
	{
		if (t == 'g')
			c = (t_hsv){130.0, 0.125, 1.0};
		if (t == 's')
			c = (t_hsv){30.0, 0.11, 1.0};
	}
	if (mlx->map == mlx->all_maps[2])
	{
		if (t == 'g')
			c = (t_hsv){30.5, 0.75, 0.5};
		if (t == 's')
			c = (t_hsv){192.0, 0.5, 0.25};
	}
	return (c);
}

void			draw_bg(t_mlx *mlx, int a, int b)
{
	double	pct;
	t_hsv	t[2];
	t_rgb	c;

	t[0] = get_bg(mlx, 'g');
	t[1] = get_bg(mlx, 's');
	while (++a < WIN_W)
	{
		b = -1;
		while (++b < WIN_H)
		{
			pct = ((double)HALF_H - (double)b) / (double)HALF_H;
			if ((HALF_H - b) < 0)
				t[0].v = d_lerp(0.125, 0.75, fabs(pct));
			else
			{
				t[1].v = d_lerp(0.1, 0.85, fabs(pct));
				t[1].s = 1.0 - t[1].v;
			}
			c = ((HALF_H - b) < 0) ? ft_hsv_to_rgb(t[0]) : ft_hsv_to_rgb(t[1]);
			img_set_pixel(mlx->bg, a, b, (c.r << 16) | (c.g << 8) | (c.b));
		}
	}
}

int				grab_color_from_tex(int x, int y, t_img *img)
{
	return (*(int *)(&(img->ptr[(y * TEX_W + x) * 4])));
}

int				loop_handler(t_mlx *mlx)
{
	static int i = 0;

	if (mlx->player->wincondition < 3)
		render(mlx);
	else
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->tex[13]->img, 0, 0);
		if (i == 0)
		{
			system("pkill afplay");
			system("afplay -v 1 sounds/ff.wav &");
		}
		i = 1;
	}
	return (0);
}
