/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 23:26:10 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/20 00:17:35 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_pixel(t_env *e, int x, int y, int color)
{
	if (x < e->reso && y < e->reso && x > 0 && y > 0)
		e->img->data[x + (y * e->reso)] = color;
}

void	draw_between(t_env *e)
{
	float	tx;
	float	dx;
	float	dy;

	tx = 0.0;
	dx = e->x1 - e->x0;
	dy = e->y1 - e->y0;
	while (tx <= 1)
	{
		e->x = e->x0 + (dx * tx);
		e->y = e->y0 + (dy * tx);
		draw_pixel(e, e->x + e->mvtx, e->y + e->mvty, e->color_display);
		tx += 1. / sqrtf((dx * dx) + (dy * dy));
	}
}

void	draw_line(t_env *e, int j, int i)
{
	e->x0 = 50 + (i * e->zoom) + (j * e->zoom);
	e->x1 = 50 + ((i + 1) * e->zoom) + (j * e->zoom);
	e->y0 = (((e->reso / 2) + (j * e->zoom)) * 1. / 2.) - (((i * e->zoom)
				+ (e->z * e->tab[j][i])) * 1. / 2.);
	e->y1 = (((e->reso / 2) + (j * e->zoom)) * 1. / 2.) - ((((i + 1) * e->zoom)
				+ (e->z * e->tab[j][i + 1])) * 1. / 2.);
	draw_between(e);
}

void	draw_col(t_env *e, int j, int i)
{
	e->x0 = 50 + (i * e->zoom) + (j * e->zoom);
	e->x1 = 50 + (i * e->zoom) + ((j + 1) * e->zoom);
	e->y0 = (((e->reso / 2) + (j * e->zoom)) * 1. / 2.) - (((i * e->zoom)
				+ (e->z * e->tab[j][i])) * 1. / 2.);
	e->y1 = (((e->reso / 2) + ((j + 1) * e->zoom)) * 1. / 2.) - (((i * e->zoom)
				+ (e->z * e->tab[j + 1][i])) * 1. / 2.);
	draw_between(e);
}

int		draw_map(t_env *e)
{
	int	i;
	int	j;

	j = 0;
	while (j < e->l)
	{
		i = 0;
		while (i < e->i - 1)
			draw_line(e, j, i++);
		j++;
	}
	j = 0;
	while (j < e->l - 1)
	{
		i = 0;
		while (i < e->i)
			draw_col(e, j, i++);
		j++;
	}
	return (0);
}
