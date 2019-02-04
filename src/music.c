/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 01:28:14 by ytran             #+#    #+#             */
/*   Updated: 2019/02/04 01:16:49 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	get_music(t_mlx *mlx)
{
	if (mlx->map == mlx->all_maps[0])
	{
		system("pkill afplay");
		//system("afplay -v 2 sounds/swt.wav &");
	}
	else if (mlx->map == mlx->all_maps[2])
	{
		system("pkill afplay");
		//system("afplay -v 2 sounds/kh3.wav &");
	}
}
