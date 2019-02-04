/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:33:23 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 00:02:05 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	error(char *str)
{
	ft_putendl(str);
	hook_close();
}

void	build_inv(t_img *tex, t_img *dest, int x, int y)
{
	int u;
	int v;
	int	color;

	v = 0;
	while (v < 64)
	{
		u = 0;
		while (u < 64)
		{
			y += x;
			color = grab_color_from_tex(u, v, tex);
			*(int *)(dest->ptr + (((x + u) + ((y + v) * 64)) * 4)) = color;
			u++;
		}
		v++;
	}
}

void	img_put_trans(t_img *src, t_img *dest, int x, int y)
{
	int	u;
	int	v;
	int	color;

	v = 0;
	while (v < src->height)
	{
		u = 0;
		while (u < src->width)
		{
			color = *(int *)(&(src->ptr[(v * src->width + u) * 4]));
			if (color != 0x9C27B0)
			{
				*(int *)(dest->ptr + (((u + x)
								+ ((y + v) * WIN_W)) * 4)) = color;
			}
			u++;
		}
		v++;
	}
}

int		dispose(t_list **lst, t_map **map)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_memdel(&(*lst)->content);
		ft_memdel((void **)lst);
		*lst = next;
	}
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->grid);
		ft_memdel((void **)map);
	}
	return (0);
}

int		uldispose(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = &(*split)[i];
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*split)[i];
	}
	ft_memdel((void **)split);
	return (0);
}
