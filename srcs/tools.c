/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 23:45:08 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/20 02:56:21 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_color(t_env *e)
{
	e->tab_c[0] = 0x00FF7F7;
	e->tab_c[1] = 0x0000FF;
	e->tab_c[2] = 0xFFFF00;
	e->tab_c[3] = 0x008000;
	e->tab_c[4] = 0x8A2BE2;
	e->tab_c[5] = 0xFF3300;
	e->tab_c[6] = 0x00CCFF;
	e->tab_c[7] = 0x996600;
	e->tab_c[8] = 0xFFCCE5;
	e->tab_c[9] = 0xFFFFFF;
	if (e->color_index == 9)
		e->color_index = 0;
	e->color_display = e->tab_c[e->color_index];
	e->color_index++;
}

int		**ft_tab(char *buffer, int nbl, int nbi, int j)
{
	int		i;
	int		k;
	int		**tab;

	k = 0;
	if (!(tab = (int **)malloc(sizeof(int *) * nbl)))
		return (NULL);
	while (buffer[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(tab[j] = (int *)malloc(sizeof(int) * nbi)))
			return (NULL);
		while (buffer[k] != '\n' && buffer[k] != '\0' && j < nbl)
		{
			tab[j][i++] = ft_atoi(buffer, &k);
			while (buffer[k] == ' ')
				k++;
		}
		k++;
		j++;
	}
	return (tab);
}

int		ft_start_struct(char *buffer, int nbl, int nbi, int i)
{
	t_env	e;

	e.reso = 1200;
	e.color_display = i;
	e.color_index = 0;
	e.z = 2.0;
	e.mvtx = 0;
	e.mvty = 0;
	e.tab = ft_tab(buffer, nbl, nbi, 0);
	e.l = nbl;
	e.i = nbi;
	if (e.l >= e.i)
		e.zoom = 400 / e.l;
	else
		e.zoom = 400 / e.i;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.reso, e.reso, "fdf");
	mlx_expose_hook(e.win, &ft_expose_hook, &e);
	mlx_key_hook(e.win, &ft_key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
