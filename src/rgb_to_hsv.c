/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 03:39:44 by amontano          #+#    #+#             */
/*   Updated: 2018/09/12 06:45:11 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "ft_color.h"

static double	ft_min(double a, double b)
{
	return (a <= b ? a : b);
}

static double	ft_max(double a, double b)
{
	return (a >= b ? a : b);
}

static double	ft_get_hue(double val, double del, t_rgb rgb)
{
	double	h;

	if (rgb.r == val)
		h = ((rgb.g - rgb.b) / del);
	else if (rgb.g == val)
		h = (2 + (rgb.b - rgb.r) / del);
	else
		h = (4 + (rgb.r - rgb.g) / del);
	h *= 60;
	h += (h < 0.0) ? 360 : 0;
	return (h);
}

static t_hsv	ft_get_hsv(double h, double s, double v)
{
	t_hsv	hsv;

	hsv.h = h;
	hsv.s = s;
	hsv.v = v / 255;
	return (hsv);
}

t_hsv			ft_rgb_to_hsv(t_rgb rgb)
{
	double	del;
	double	min;
	double	hue;
	double	sat;
	double	val;

	min = ft_min(ft_min(rgb.r, rgb.g), rgb.b);
	val = ft_max(ft_max(rgb.r, rgb.g), rgb.b);
	del = val - min;
	sat = (val == 0.0) ? 0.0 : (del / val);
	hue = (sat == 0) ? 0.0 : ft_get_hue(val, del, rgb);
	return (ft_get_hsv(hue, sat, val));
}
