/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 23:28:22 by amontano          #+#    #+#             */
/*   Updated: 2018/09/13 02:00:44 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_shaders(t_hsv *hsv, int wallh)
{
	double	pct;

	pct = ((double)wallh / (double)WIN_H);
	pct = (pct < 0) ? 0.0 : pct;
	pct = (pct > 1) ? 1.0 : pct;
	hsv->v *= d_lerp(0.15, 1.0, pct);
}

void	draw_line(int x, t_ray *r, t_mlx *mlx)
{
	int		start;
	int		stop;
	int		color;
	t_hsv	hsv;
	t_rgb	tmp;

	start = HALF_H - r->h / 2;
	start = (start < 0) ? 0 : start;
	stop = start + r->h;
	stop = (stop > WIN_H - 1) ? WIN_H - 1 : stop;
	while (start < stop)
	{
		hsv = *mlx->hsvtex[r->texnum][get_tex_y(r, start) * TEX_W	\
										+ get_tex_x(r, mlx->player)];
		draw_shaders(&hsv, r->h);
		tmp = ft_hsv_to_rgb(hsv);
		color = (tmp.r << 16) | (tmp.g << 8) | (tmp.b);
		if (r->side)
			color = (color >> 1) & 0x7F7F7F;
		img_set_pixel(mlx->img, x, start, color);
		start++;
	}
}

void	*render_thread(void *param)
{
	t_ray	r;
	t_argp	*p;
	int		x;
	int		i;

	p = (t_argp *)param;
	i = 0;
	x = p->id;
	while (i < WIN_W / THREADS)
	{
		shoot_ray(&r, p->mlx->player, x, p);
		draw_line(x, &r, p->mlx);
		i++;
		x += THREADS;
	}
	pthread_exit(0);
}

void	clear_zbuf(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < WIN_W)
	{
		mlx->zbuf[i] = 0;
		i++;
	}
}

int		render(t_mlx *mlx)
{
	int			i;
	pthread_t	th[THREADS + 1];
	t_argp		argp[THREADS];

	mlx->img->ptr = (char *)ft_memcpy(mlx->img->ptr, mlx->bg->ptr, TMEM);
	pthread_create(&th[THREADS], NULL, manage_moves, mlx);
	i = -1;
	while (++i < THREADS)
	{
		argp[i].mlx = mlx;
		argp[i].id = i;
		pthread_create(&th[i], NULL, render_thread, &argp[i]);
	}
	i = -1;
	while (++i < (THREADS + 1))
		pthread_join(th[i], NULL);
	if (mlx->sprites)
		draw_sprites(mlx, mlx->player, mlx->n_sprites);
	img_put_trans(mlx->inv, mlx->img, WIN_W - 96, 32);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	draw_inventory(mlx);
	draw_hud(mlx);
	clear_zbuf(mlx);
	return (0);
}
