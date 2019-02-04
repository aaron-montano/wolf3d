/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 04:18:31 by amontano          #+#    #+#             */
/*   Updated: 2018/09/12 06:46:01 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "ft_color.h"

static void		arrange_values(double rgb[3], double a, double b, double c)
{
	rgb[0] = a;
	rgb[1] = b;
	rgb[2] = c;
}

static void		get_intensity(double rgb[3], double h, double s, double v)
{
	double	f;
	double	p;
	double	q;
	double	t;
	int		i;

	i = (int)trunc(h);
	f = h - i;
	p = v * (1.0 - s);
	q = v * (1.0 * (s * f));
	t = v * (1.0 - (s * (1.0 - f)));
	if (i == 0)
		arrange_values(rgb, v, t, p);
	else if (i == 1)
		arrange_values(rgb, q, v, p);
	else if (i == 2)
		arrange_values(rgb, p, v, t);
	else if (i == 3)
		arrange_values(rgb, p, q, v);
	else if (i == 4)
		arrange_values(rgb, t, p, v);
	else
		arrange_values(rgb, v, p, q);
}

t_rgb			ft_hsv_to_rgb(t_hsv hsv)
{
	double	rgb[3];
	t_rgb	ret;

	if (hsv.s == 0)
	{
		rgb[0] = hsv.v;
		rgb[1] = hsv.v;
		rgb[2] = hsv.v;
	}
	else
	{
		hsv.h = (hsv.h == 360) ? 0 : (hsv.h / 60.0);
		get_intensity(rgb, hsv.h, hsv.s, hsv.v);
	}
	ret.r = rgb[0] * 255;
	ret.g = rgb[1] * 255;
	ret.b = rgb[2] * 255;
	return (ret);
}

int				get_tex_y(t_ray *r, int y)
{
	return (((y - WIN_H * 0.5 + r->h * 0.5) * TEX_W) / r->h);
}

int				get_tex_x(t_ray *r, t_pc *p)
{
	double	wallx;
	int		tex_x;

	if (r->side == 0)
		wallx = p->y + r->perp * r->rdy;
	else
		wallx = p->x + r->perp * r->rdx;
	wallx -= floor(wallx);
	tex_x = (wallx * TEX_W);
	if ((r->side == 0 && r->rdx > 0) || (r->side == 1 && r->rdy < 0))
		tex_x = TEX_W - tex_x - 1;
	return (tex_x);
}
