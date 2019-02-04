/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:15:08 by amontano          #+#    #+#             */
/*   Updated: 2018/08/21 23:40:03 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_tile			*set_tile(int x, int y, char *str)
{
	t_tile	*t;
	char	c;

	c = str[0];
	t = (t_tile *)ft_memalloc(sizeof(t_tile));
	if (t == NULL || str[1])
		return (NULL);
	t->x = x;
	t->y = y;
	t->sprite = '\0';
	t->properties = 0;
	if (c >= '0' && c <= '9')
		t->properties = ft_atoi(str);
	if (c == '9')
		t->sprite = 'E';
	if (c == 'C' || c == 'Y' || c == 'R' || c == 'T' || c == 'F')
		t->sprite = c;
	if (c == 'B')
	{
		t->properties = 5;
		t->sprite = ((x + y) % 2 == 0) ? 'C' : 'R';
	}
	return (t);
}

static int		fill_map(t_map **m, t_list *list)
{
	t_list		*cursor;
	char		**split;
	int			x;
	int			y;

	cursor = list;
	y = 0;
	while (y < (*m)->h)
	{
		x = -1;
		if ((split = ft_strsplit(cursor->content, ' ')) == NULL)
			return (dispose(&list, m));
		(*m)->grid[y] = (t_tile **)malloc(sizeof(t_tile *) * (*m)->w);
		while (++x < (*m)->w)
			if (!((*m)->grid[y][x] = set_tile(x, y, split[x])))
				return (0);
		uldispose(&split);
		cursor = cursor->next;
		y++;
	}
	checkmap(*m);
	dispose(&list, NULL);
	return (1);
}

static t_map	*gen_map(int width, int height)
{
	t_map *map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->w = width;
	map->h = height;
	if (map->w > 64 || map->h > 64)
		error("map too big");
	map->grid = (t_tile ***)ft_memalloc(sizeof(t_tile **) * height);
	if (!(map->grid))
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}

static int		read_lines(int fd, t_list **lst)
{
	t_list	*tmp;
	int		fin;
	int		ret;
	char	*line;

	fin = -1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (fin == -1)
			fin = ft_wordcount_d(line, ' ');
		tmp = ft_lstnew(line, ft_strlen(line) + 1);
		if ((tmp) == NULL)
			return (dispose(lst, NULL));
		ft_lstadd(lst, tmp);
		if (fin != ft_wordcount_d(line, ' '))
			return (dispose(lst, NULL));
		ft_strdel(&line);
	}
	if (fin == -1 || ret == -1)
		return (dispose(lst, NULL));
	return (1);
}

int				read_file(int fd, t_map **map)
{
	t_list *lst;

	lst = NULL;
	if (!(read_lines(fd, &lst)))
		return (0);
	*map = gen_map((int)ft_wordcount_d(lst->content, ' '),
			(int)ft_lstcount(lst));
	if (*map == NULL)
		return (dispose(&lst, map));
	return (fill_map(map, lst));
}
