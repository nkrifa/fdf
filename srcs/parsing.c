/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 23:30:18 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/18 23:54:23 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_hexa(char *buffer, int i, int num, int start)
{
	if (buffer[i - 1] < '0' || buffer[i - 1] > '9')
		return (-1);
	i++;
	if (buffer[i] != '0' || buffer[i + 1] != 'x' || buffer[num] != ' ')
		return (-1);
	i += 2;
	while (i < num)
	{
		if ((buffer[i] < '0' || buffer[i] > '9') && (buffer[i] < 'A' \
					|| buffer[i] > 'F'))
			return (-1);
		i++;
	}
	while (start < num)
	{
		buffer[start] = ' ';
		start++;
	}
	return (1);
}

int		ft_length_error(char *buff)
{
	t_env e;

	e.i = 0;
	e.length = -1;
	while (buff[e.i] != '\0')
	{
		e.l = 0;
		while (buff[e.i] == ' ')
			e.i++;
		while (buff[e.i] != '\n' && buff[e.i] != '\0')
		{
			while (buff[e.i] == ' ' && buff[e.i] != '\n' && buff[e.i] != '\0')
				e.i++;
			if (buff[e.i] != '\n' && buff[e.i] != '\0')
				e.l++;
			while (buff[e.i] != ' ' && buff[e.i] != '\n' && buff[e.i] != '\0')
				e.i++;
		}
		if (e.length == -1)
			e.length = e.l;
		else if (e.l != e.length)
			return (-1);
		e.i++;
	}
	return (e.length);
}

int		ft_start_error(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if ((buffer[i] < '0' || buffer[i] > '9') \
				&& buffer[i] != '-' && buffer[i] != ' ')
		{
			ft_putstr_fd(LINE_ERROR, 2);
			return (-1);
		}
		while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
		i++;
	}
	return (1);
}

int		ft_invalid(char *buffer, int i)
{
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '-' && (buffer[i + 1] < '0' || buffer[i + 1] > '9'))
		{
			ft_putstr_fd(CHAR_ERROR, 2);
			return (-1);
		}
		if (buffer[i] != '-' && buffer[i] != ' ' && buffer[i] != '\n'\
				&& !(buffer[i] >= '0' && buffer[i] <= '9'))
		{
			if (buffer[i] == ',' && ft_hexa(buffer, i, i + 9, i) == -1)
			{
				ft_putstr_fd(CHAR_ERROR, 2);
				return (-1);
			}
			else
			{
				ft_putstr_fd(LINE_ERROR, 2);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

char	*ft_endbuffer(char *buffer, int *length)
{
	int		i;

	i = 0;
	if (buffer[0] == '\0')
	{
		ft_putstr_fd(READ_ERROR, 2);
		return (NULL);
	}
	while (buffer[i] != '\0')
		i++;
	buffer[i - 1] = '\0';
	if (ft_start_error(buffer) == -1 || ft_invalid(buffer, 0) == -1)
		return (NULL);
	if ((*length = ft_length_error(buffer)) == -1)
	{
		ft_putstr_fd(LINE_ERROR, 2);
		return (NULL);
	}
	return (buffer);
}
