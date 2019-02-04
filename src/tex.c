/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 21:18:16 by amontano          #+#    #+#             */
/*   Updated: 2018/09/13 01:05:40 by ytran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		free_textures(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < TEX_SZ)
		del_img(mlx, mlx->tex[i++]);
}

t_img			*xpm_image(char *xpm, t_mlx *mlx)
{
	t_img	*img;

	if ((img = ft_memalloc(sizeof(t_img))) == NULL)
		return (NULL);
	if ((img->img = mlx_xpm_file_to_image(mlx->mlx, xpm,
					&img->width, &img->height)) == NULL)
		return (del_img(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bpp,
			&img->stride, &img->endian);
	img->bpp /= 8;
	img->width = img->stride / img->bpp;
	img->height = img->stride / img->bpp;
	return (img);
}

t_hsv			**ft_img_to_hsv(t_img *i)
{
	int		c;
	t_hsv	**ret;
	t_rgb	tmp;
	int		y;
	int		x;

	y = 0;
	ret = (t_hsv **)ft_memalloc(sizeof(t_hsv *) * (TEX_W * TEX_W));
	while (y < TEX_W)
	{
		x = 0;
		while (x < TEX_W)
		{
			c = grab_color_from_tex(x, y, i);
			tmp = (t_rgb){((c >> 16) & 0xFF), ((c >> 8) & 0xFF), (c & 0xFF)};
			ret[y * TEX_W + x] = (t_hsv *)malloc(sizeof(t_hsv));
			*ret[y * TEX_W + x] = ft_rgb_to_hsv(tmp);
			x++;
		}
		y++;
	}
	return (ret);
}

int				load_textures(t_mlx *mlx)
{
	static char *map[TEX_SZ] = {
		"bluestone.xpm", "purplestone.xpm", "mossy.xpm", "redbrick.xpm",
		"qbox.xpm", "companion_cube.xpm", "bluepipe.xpm",
		"coin.xpm", "yoshicoin.xpm", "rupee.xpm", "triforce.xpm",
		"42logo.xpm", "youwwin.xpm", NULL
	};
	t_img		*img;
	int			i;
	char		*t;

	i = 1;
	while (i < TEX_SZ && map[i - 1])
	{
		t = ft_strjoin("textures/", map[i - 1]);
		img = tex_helper(mlx, t);
		ft_strdel(&t);
		mlx->tex[i] = img;
		mlx->hsvtex[i] = ft_img_to_hsv(mlx->tex[i]);
		i++;
	}
	mlx->tex[0] = NULL;
	mlx->hsvtex[0] = NULL;
	return (0);
}

t_img			*tex_helper(t_mlx *mlx, char *t)
{
	t_img	*img;

	if ((img = xpm_image(t, mlx)) == NULL)
	{
		ft_strdel(&t);
		free_textures(mlx);
		error("image failed to upload");
	}
	return (img);
}
