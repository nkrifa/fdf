/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 23:22:50 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/20 03:13:03 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_expose_hook(t_env *e)
{
	e->img->img_ptr = mlx_new_image(e->mlx, e->reso, e->reso);
	e->img->data = (int *)mlx_get_data_addr(e->img->img_ptr, &e->img->bpp\
		, &e->img->size_l, &e->img->endian);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img_ptr, 0, 0);
	draw_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img_ptr, 0, 0);
	mlx_string_put(e->mlx, e->win, 10, e->reso - 50, 0xFFFFCC,\
		"| End with esc | Keyboard arrows to Move | Zoom with Q W |");
	mlx_string_put(e->mlx, e->win, 10, e->reso - 33, 0xFFFFCC, \
		"| Color with T |      Depth with E R     |");
	return (0);
}

int		ft_key_hook2(int keycode, t_env *e)
{
	if (keycode == ADD_D)
	{
		if (e->z <= 30.)
			e->z += 0.1;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == RM_D)
	{
		if (e->z >= -30.)
			e->z -= 0.1;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == COLOR_N)
	{
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_color(e);
		ft_expose_hook(e);
	}
	return (0);
}

int		ft_key_hook3(int keycode, t_env *e)
{
	if (keycode == UP)
	{
		e->mvty -= 30;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == CORTEX)
	{
		if (e->zoom <= 95)
			e->zoom += 1;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == MINUS)
	{
		if (e->zoom > 0)
			e->zoom -= 1;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	ft_key_hook2(keycode, e);
	return (0);
}

int		ft_key_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)
	{
		e->mvtx -= 30;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == RIGHT)
	{
		e->mvtx += 30;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	if (keycode == DOWN)
	{
		e->mvty += 30;
		mlx_destroy_image(e->mlx, e->img->img_ptr);
		ft_expose_hook(e);
	}
	ft_key_hook3(keycode, e);
	return (0);
}
