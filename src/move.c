/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 04:20:33 by ytran             #+#    #+#             */
/*   Updated: 2018/09/12 04:31:24 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		strafe(t_mlx *mlx, double dir)
{
	double	spd;
	int		tx;
	int		ty;

	spd = !(mlx->kb->run) ? STEP_SZ : STEP_SZ * 2;
	spd *= dir;
	tx = get_tile(mlx->map, mlx->player->x + spd
			* mlx->player->camx, mlx->player->y);
	tx = (tx >= 8) ? 0 : tx;
	ty = get_tile(mlx->map, mlx->player->x, mlx->player->y
			+ spd * mlx->player->camy);
	ty = (ty >= 8) ? 0 : ty;
	if (tx == 0)
		mlx->player->x += (ty == 0) ? spd * mlx->player->camx
			: (spd / 8.0) * mlx->player->camx;
	if (ty == 0)
		mlx->player->y += (tx == 0) ? spd * mlx->player->camy
			: (spd / 8.0) * mlx->player->camy;
}

void		move(t_mlx *mlx, double dir)
{
	double	spd;
	int		tx;
	int		ty;

	spd = !(mlx->kb->run) ? STEP_SZ : STEP_SZ * 2;
	spd *= dir;
	tx = get_tile(mlx->map, mlx->player->x
			+ spd * mlx->player->dirx, mlx->player->y);
	tx = (tx >= 8) ? 0 : tx;
	ty = get_tile(mlx->map, mlx->player->x, mlx->player->y
			+ spd * mlx->player->diry);
	ty = (ty >= 8) ? 0 : ty;
	if (tx == 0)
	{
		mlx->player->x += (ty == 0) ?
			(spd * mlx->player->dirx) : (spd / 8.0) * mlx->player->dirx;
	}
	if (ty == 0)
	{
		mlx->player->y += (tx == 0) ?
			(spd * mlx->player->diry) : (spd / 8.0) * mlx->player->diry;
	}
}

void		rotate(t_pc *p, int dir, double rot)
{
	double old;
	double cold;
	double c;
	double s;

	old = p->dirx;
	cold = p->camx;
	c = cos(rot * dir);
	s = sin(rot * dir);
	p->dirx = p->dirx * c - p->diry * s;
	p->diry = old * s + p->diry * c;
	p->camx = p->camx * c - p->camy * s;
	p->camy = cold * s + p->camy * c;
	p->angle += (int)floor(rot * 180.0 / M_PI) * dir;
	if (p->angle >= 360)
		p->angle %= 360;
	if (p->angle < 0)
		p->angle += 360;
}

void		move_helper(t_mlx *mlx, int key)
{
	if (key == KEY_W || key == KEY_UP)
		mlx->kb->f = 0;
	if (key == KEY_S || key == KEY_DOWN)
		mlx->kb->b = 0;
	if (key == KEY_A)
		mlx->kb->l = 0;
	if (key == KEY_D)
		mlx->kb->r = 0;
	if (key == KEY_LEFT)
		mlx->kb->rot_l = 0;
	if (key == KEY_RIGHT)
		mlx->kb->rot_r = 0;
	if (key == KEY_TAB)
		mlx->kb->run ^= 0x1;
}
