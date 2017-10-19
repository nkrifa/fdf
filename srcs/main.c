/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 23:39:08 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/19 23:55:46 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_start(char *argv, int argc, int *fd)
{
	if (argc == 1)
	{
		ft_putstr_fd("fdf needs one fdf file to run", 2);
		return (-1);
	}
	if (argc > 2)
	{
		ft_putstr_fd(READ_ERROR, 2);
		return (-1);
	}
	if (BUFF_SIZE < 1)
	{
		ft_putstr_fd("Error with buff size", 2);
		return (-1);
	}
	if ((*fd = open(argv, O_RDONLY)) == -1)
	{
		ft_putstr_fd(READ_ERROR, 2);
		return (-1);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int		nbl;
	int		nbi;
	int		fd;
	char	*line;
	char	*buffer;

	nbl = 0;
	buffer = ft_strnew(1);
	if (ft_start(argv[1], argc, &fd) == -1)
		return (0);
	while (get_next_line(fd, &line) > 0 && nbl++ > -1)
		buffer = ft_strjoin(ft_strjoin(buffer, line), "\n");
	if (get_next_line(fd, &line) != 0)
	{
		ft_putstr_fd(READ_ERROR, 2);
		free(buffer);
		return (0);
	}
	if (ft_endbuffer(buffer, &nbi) != NULL)
		ft_init_struct(buffer, nbl, nbi, 0xFFFFFF);
	if (close(fd) == -1)
		ft_putstr_fd(READ_ERROR, 2);
	return (0);
}
