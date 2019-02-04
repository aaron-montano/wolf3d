/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 17:31:50 by amontano          #+#    #+#             */
/*   Updated: 2019/02/04 01:15:43 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_mlx		*mlx_dispose(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img)
		del_img(mlx, mlx->img);
	if (mlx->kb)
		ft_memdel((void **)&mlx->kb);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->mlx = mlx_init()) \
			|| (!(mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H,
						"42-Silicon Valley : Wolf3D -- amontano and ytran"))) \
			|| (!(mlx->img = new_img(mlx))) \
			|| (!(mlx->bg = new_img(mlx)))	\
			|| (!(mlx->kb = (t_kb *)malloc(sizeof(t_kb))))
			|| (!(mlx->hsvtex = (t_hsv ***)malloc(sizeof(t_hsv **) * TEX_SZ))))
	{
		ft_putendl("mlx failed to init");
		return (mlx_dispose(mlx));
	}
	// audio files too large for upload
	 //system("afplay -v 2 sounds/swt.wav &");
	return (mlx);
}

int			hook_close(void)
{
	system("pkill afplay");

	exit(0);
}

t_map		**init_maps(void)
{
	t_map	**all_maps;
	int		fd[N_MAPS];
	int		i;
	char	*path;
	char	*n;

	i = -1;
	if (!(all_maps = (t_map **)ft_memalloc(sizeof(t_map *) * N_MAPS + 1)))
		return (NULL);
	while (++i < N_MAPS)
	{
		n = ft_itoa(i + 1);
		path = ft_strjoin("maps/txt.m", n);
		fd[i] = open(path, O_RDONLY);
		if (read_file(fd[i], &all_maps[i]))
			all_maps[i]->id = i;
		else
			error("invalid map");
		ft_strdel(&path);
		ft_strdel(&n);
	}
	all_maps[N_MAPS] = NULL;
	while (i >= 0)
		close(fd[i--]);
	return (all_maps);
}

int			main(void)
{
	t_mlx *mlx;

	if ((mlx = init()) == NULL)
		error("mlx failed to init");
	if ((mlx->all_maps = init_maps()) == NULL)
		error("maps failed to init");
	mlx->map = mlx->all_maps[0];
	if (load_textures(mlx) == 1)
		error("textures failed to load");
	if ((mlx->sprites = init_sprites(mlx)) == NULL)
		error("sprites failed to init");
	if ((mlx->player = init_player(mlx)) == NULL)
		error("player failed to init");
	if ((mlx->inv = init_inventory(mlx)) == NULL)
		error("inventory failed to init");
	draw_bg(mlx, -1, -1);
	mlx_hook(mlx->win, 2, 0, hook_key_down, mlx);
	mlx_hook(mlx->win, 3, 0, hook_key_up, mlx);
	mlx_hook(mlx->win, 17, 0, hook_close, mlx);
	mlx_loop_hook(mlx->mlx, &loop_handler, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
