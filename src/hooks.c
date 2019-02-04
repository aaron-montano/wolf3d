/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:11:56 by amontano          #+#    #+#             */
/*   Updated: 2018/09/12 04:30:00 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			get_tile(t_map *m, int x, int y)
{
	if (x < 0 || y < 0 || x > m->w - 1 || y > m->h - 1)
		return (0);
	return (m->grid[y][x]->properties);
}

void		*manage_moves(void *mlx_ptr)
{
	t_mlx				*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (mlx->kb->rot_l)
		rotate(mlx->player, 1, ROT_SZ);
	if (mlx->kb->rot_r)
		rotate(mlx->player, -1, ROT_SZ);
	if (mlx->kb->l)
		strafe(mlx, -1);
	if (mlx->kb->r)
		strafe(mlx, 1);
	if (mlx->kb->f)
		move(mlx, 1);
	if (mlx->kb->b)
		move(mlx, -1);
	pthread_exit(0);
}

int			hook_key_down(int key, t_mlx *mlx)
{
	if (key == KEY_W || key == KEY_UP)
		mlx->kb->f = 1;
	if (key == KEY_S || key == KEY_DOWN)
		mlx->kb->b = 1;
	if (key == KEY_A)
		mlx->kb->l = 1;
	if (key == KEY_D)
		mlx->kb->r = 1;
	if (key == KEY_LEFT)
		mlx->kb->rot_l = 1;
	if (key == KEY_RIGHT)
		mlx->kb->rot_r = 1;
	return (0);
}

void		item_select(t_pc *p, int move)
{
	p->select += move;
	if (p->select == 7)
		p->select = 2;
	if (p->select == 1)
		p->select = 6;
}

int			hook_key_up(int key, t_mlx *mlx)
{
	move_helper(mlx, key);
	if (key == KEY_E)
		pickup(mlx, mlx->map);
	if (key == KEY_T)
		scan_event(mlx);
	if (key == KEY_R)
		drop(mlx, mlx->map);
	if (key == KEY_1)
		item_select(mlx->player, -1);
	if (key == KEY_2)
		item_select(mlx->player, 1);
	if (key == KEY_ESC)
		hook_close();
	return (0);
}
