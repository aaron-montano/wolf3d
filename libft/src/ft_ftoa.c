/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 04:06:49 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 04:06:54 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ftoa(double f, unsigned int acc)
{
	char	*tmpi;
	char	*tmpf;
	char	*t;
	char	*a;
	int		d;

	d = (acc > 0) ? 10 : 1;
	while (acc > 1)
	{
		d *= 10;
		acc--;
	}
	tmpi = ft_itoa(f);
	tmpf = ft_itoa(d * (f - (int)f));
	t = ft_strjoin(tmpi, ".");
	a = ft_strjoin(t, tmpf);
	ft_strdel(&tmpi);
	ft_strdel(&tmpf);
	ft_strdel(&t);
	return (a);
}
