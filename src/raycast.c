/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:10:47 by amontano          #+#    #+#             */
/*   Updated: 2018/09/13 23:58:20 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**  t_vec all[5] is all of the variables needed to calculate a ray
**  their names are as follows:
**  all[0] = raydir; ray direction (x and y)
**  all[1] = side_dist; accumlated distance (x and y)
**  all[2] = delta_dist; partial distance (x and y)
**  all[3] = step; 1 or 0 (a and b)
**  all[4] = m; map coords (uses a and b)
*/

static void		init_ray(t_vec all[5], t_pc *pc, double cam_x)
{
	all[0].x = pc->dirx + pc->camx * cam_x;
	all[0].y = pc->diry + pc->camy * cam_x;
	all[4].a = pc->x;
	all[4].b = pc->y;
	all[2].x = fabs(1 / all[0].x);
	all[2].y = fabs(1 / all[0].y);
	all[3].a = (all[0].x < 0) ? -1 : 1;
	all[1].x = (all[0].x < 0) ? (pc->x - all[4].a) * all[2].x : \
		(all[4].a + 1.0 - pc->x) * all[2].x;
	all[3].b = (all[0].y < 0) ? -1 : 1;
	all[1].y = (all[0].y < 0) ? (pc->y - all[4].b) * all[2].y : \
		(all[4].b + 1.0 - pc->y) * all[2].y;
}

static int		get_side(t_vec all[5])
{
	if (all[1].x < all[1].y)
	{
		all[1].x += all[2].x;
		all[4].a += all[3].a;
		return (0);
	}
	else
	{
		all[1].y += all[2].y;
		all[4].b += all[3].b;
		return (1);
	}
}

void			shoot_ray(t_ray *ray, t_pc *pc, int x, t_argp *p)
{
	t_vec	all[5];
	double	cam_x;

	cam_x = (double)x / (double)HALF_W - 1;
	init_ray(all, pc, cam_x);
	check_hit(ray, p, all);
	if (ray->side == 0)
		ray->perp = (all[4].a - pc->x + (1 - all[3].a) / 2.0) / all[0].x;
	else
		ray->perp = (all[4].b - pc->y + (1 - all[3].b) / 2.0) / all[0].y;
	ray->h = (int)floor(WIN_H / (ray->perp));
	p->mlx->zbuf[x] = ray->perp;
}

void			check_hit(t_ray *ray, t_argp *p, t_vec all[5])
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		ray->side = get_side(all);
		hit = p->mlx->map->grid[all[4].b][all[4].a]->properties;
		hit = (hit >= 8) ? 0 : hit;
		if (hit > 0)
		{
			ray->sdx = all[1].x;
			ray->sdy = all[1].y;
			ray->rdx = all[0].x;
			ray->rdy = all[0].y;
			ray->texnum = hit;
		}
	}
}
