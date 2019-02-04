/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 05:35:55 by amontano          #+#    #+#             */
/*   Updated: 2018/09/12 06:41:49 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

typedef struct	s_rgb
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_rgb;

typedef struct	s_hsv
{
	double h;
	double s;
	double v;
}				t_hsv;

t_hsv			ft_rgb_to_hsv(t_rgb rgb);
t_rgb			ft_hsv_to_rgb(t_hsv hsv);
double			d_lerp(double min, double max, double pct);
#endif
