/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkrifa <nkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 17:29:59 by nkrifa            #+#    #+#             */
/*   Updated: 2017/10/18 02:23:02 by nkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libftprint.h"

#include "./get_next_line/get_next_line.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
# include <errno.h>

typedef enum Couleur Couleur;
enum Couleur
{
    Rouge = 0x00FF7F7,
    Bleu = 0x0000FF,
    Jaune = 0xFFFF00,
    Vert = 0x008000,
    Violet = 0x8A2BE2,
    Orange = 0xFF3300,
    Cyan = 0x00CCFF,
    Marron = 0x996600,
    Noir = 0x00000000,
    Blanc = 0xFFFFFF,
};


#define TAILLE 10

typedef struct  s_env
{
    int			l;
	int			i;
	int			length;
	int			zoom;
	int			xmove;
	int			ymove;
	double		z;
	int			**tab;
	double		x;
	double		y;
	double		x0;
	double		x1;
	double		y0;
	double		y1;
	void		*mlx;
	void		*win;
}               t_env;


int			ft_key_hook(int keycode, t_env *e);
void    draw_between(t_env *e);
void    draw_line(t_env *e, int i, int j);
void    draw_col(t_env *e, int i, int j);
int			draw_map(t_env *e);
int			**ft_newtab(char *buf, int nbl, int nbi, int j);
int			ft_init_struct(char *buf, int nbl, int nbi);
int	ft_start(char *argv, int argc, int *fd);
int			ft_expose_hook(t_env *e);
int	ft_key3(int keycode, t_env *e);
int	ft_key2(int keycode, t_env *e);
int			ft_key_hook(int keycode, t_env *e);








void    ft_draw_line(t_env *e)
{
    
     double tx;
     float dx;
     float dy;

     tx = 0.0;
     dx = e->x1 - e->x0;
     dy = e->x1 - e->x0;
     while(tx <= 1)
     {
         e->x = e->x0 + (dx * tx);
         e->y = e->y0 + (dy * tx);
         mlx_pixel_put(e->mlx, e->win, e->x, e->y, 0x00FF7F7);
         tx += 1. / sqrt((dx * dx) + (dy * dy)); 
     }
}

/*void    draw_line(t_env *e, int j, int i)
{
    e->x0= 50 + (i * e->zoom) + (j * e->zoom);
    e->x1 =  50 + (i * e->zoom) + ((j + 1) * e->zoom);
    e->y0 = ((700 + (j * e->zoom)) * 1. / 2.) - (((i * e->zoom) + (e->z * e->tab[j][i])) * 1. / 2.);
    e->y1 = ((700 + (j + 1)) * 1. / 2.) - ((i+ (e->z * e->tab[j + 1][i])) * 1. / 2.);
    draw_between(e);
}

void    draw_col(t_env *e, int i, int j)
{
    e->x0 = 50 + (i * e->zoom) + (j * e->zoom);
	e->x1 = 50 + ((i + 1) * e->zoom) + (j * e->zoom);
	e->y0 = ((700 + (j * e->zoom)) * 1. / 2.) - (((i * e->zoom)
	+ (e->z * e->tab[j][i])) * 1. / 2.);
	e->y1 = ((700 + (j * e->zoom)) * 1. / 2.) - ((((i + 1) * e->zoom)
	+ (e->z * e->tab[j][i + 1])) * 1. / 2.);
	draw_between(e);
}

int			draw_map(t_env *e)
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
*/

void	ft_vertical(t_env *f, int j, int i)
{
	f->x0 = 50 + (i * f->zoom) + (j * f->zoom);
	f->x1 = 50 + (i * f->zoom) + ((j + 1) * f->zoom);
	f->y0 = ((700 + (j * f->zoom)) * 1. / 2.) - (((i * f->zoom)
				+ (f->z * f->tab[j][i])) * 1. / 2.);
	f->y1 = ((700 + (j + 1)) * 1. / 2.) - ((i
				+ (f->z * f->tab[j + 1][i])) * 1. / 2.);
	ft_draw_line(f);
}

void	ft_horizontal(t_env *f, int j, int i)
{
	f->x0 = 50 + (i * f->zoom) + (j * f->zoom);
	f->x1 = 50 + ((i + 1) * f->zoom) + (j * f->zoom);
	f->y0 = ((700 + (j * f->zoom)) * 1. / 2.) - (((i * f->zoom)
				+ (f->z * f->tab[j][i])) * 1. / 2.);
	f->y1 = ((700 + (j * f->zoom)) * 1. / 2.) - ((((i + 1) * f->zoom)
				+ (f->z * f->tab[j][i + 1])) * 1. / 2.);
	ft_draw_line(f);
}

int			ft_call(t_env *f)
{
	int	i;
	int	j;

	j = 0;
	while (j < f->l)
	{
		i = 0;
		while (i < f->i - 1)
			ft_horizontal(f, j, i++);
		j++;
	}
	j = 0;
	while (j < f->l - 1)
	{
		i = 0;
		while (i < f->i)
			ft_vertical(f, j, i++);
		j++;
	}
	return (0);
}

int			ft_init_struct(char *buf, int nbl, int nbi)
{
	t_env	f;

	f.z = 2.0;
	f.xmove = 0;
	f.ymove = 0;
	f.tab = ft_newtab(buf, nbl, nbi, 0);
	f.l = nbl;
	f.i = nbi;
	if (f.l >= f.i)
		f.zoom = 400 / f.l;
	else
		f.zoom = 400 / f.i;
	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, 800, 800, "fdf");
	mlx_expose_hook(f.win, &ft_expose_hook, &f);
	mlx_key_hook(f.win, &ft_key_hook, &f);
	mlx_loop(f.mlx);
	return (0);
}




int			ft_expose_hook(t_env *e)
{
	int	x;
	int	y;

	x = 27;
	y = 34;
	while (x <= 180)
		mlx_pixel_put(e->mlx, e->win, x++, y, 0x0000FF);
	while (y <= 117)
		mlx_pixel_put(e->mlx, e->win, x, y++, 0x0000FF);
	while (x >= 27)
		mlx_pixel_put(e->mlx, e->win, x--, y, 0x0000FF);
	while (y >= 34)
		mlx_pixel_put(e->mlx, e->win, x, y--, 0x0000FF);
	mlx_string_put(e->mlx, e->win, 35, 35, 0x0000FF, "Quit = ESC");
	mlx_string_put(e->mlx, e->win, 35, 55, 0x0000FF, "Move = ^ v < >");
	mlx_string_put(e->mlx, e->win, 35, 75, 0x0000FF, "Zoom = + -");
	mlx_string_put(e->mlx, e->win, 35, 95, 0x0000FF, "Depth = w s");
	ft_call(e);
	return (0);
}

int	ft_key3(int keycode, t_env *e)
{
	if (keycode == 13)
	{
		if (e->z <= 30.)
			e->z += 0.1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == 1)
	{
		if (e->z >= -30.)
			e->z -= 0.1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	return (0);
}

int	ft_key2(int keycode, t_env *e)
{
	if (keycode == 126)
	{
		e->ymove -= 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == 69)
	{
		if (e->zoom <= 95)
			e->zoom += 1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == 78)
	{
		if (e->zoom >= -35)
			e->zoom -= 1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	ft_key3(keycode, e);
	return (0);
}

int			ft_key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
	{
		e->xmove -= 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == 124)
	{
		e->xmove += 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == 125)
	{
		e->ymove += 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	ft_key2(keycode, e);
	return (0);
}

static int	ft_hexa(char *buf, int i, int num, int start)
{
	if (buf[i - 1] < '0' || buf[i - 1] > '9')
		return (-1);
	i++;
	if (buf[i] != '0' || buf[i + 1] != 'x' || buf[num] != ' ')
		return (-1);
	i += 2;
	while (i < num)
	{
		if ((buf[i] < '0' || buf[i] > '9') && (buf[i] < 'A' || buf[i] > 'F'))
			return (-1);
		i++;
	}
	while (start < num)
	{
		buf[start] = ' ';
		start++;
	}
	return (1);
}

static int	ft_length_error(char *buf)
{
	t_env v;

	v.i = 0;
	v.length = -1;
	while (buf[v.i] != '\0')
	{
		v.l = 0;
		while (buf[v.i] == ' ')
			v.i++;
		while (buf[v.i] != '\n' && buf[v.i] != '\0')
		{
			while (buf[v.i] == ' ' && buf[v.i] != '\n' && buf[v.i] != '\0')
				v.i++;
			if (buf[v.i] != '\n' && buf[v.i] != '\0')
				v.l++;
			while (buf[v.i] != ' ' && buf[v.i] != '\n' && buf[v.i] != '\0')
				v.i++;
		}
		if (v.length == -1)
			v.length = v.l;
		else if (v.l != v.length)
			return (-1);
		v.i++;
	}
	return (v.length);
}

static int	ft_start_error(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] != '\0')
	{
		if ((buf[i] < '0' || buf[i] > '9') && buf[i] != '-' && buf[i] != ' ')
		{
			ft_putstr_fd("error: lines must start by a digit or space\n", 2);
			return (-1);
		}
		while (buf[i] != '\n' && buf[i] != '\0')
			i++;
		i++;
	}
	return (1);
}

static int	ft_invalid(char *buf, int i)
{
	while (buf[i] != '\0')
	{
		if (buf[i] == '-' && (buf[i + 1] < '0' || buf[i + 1] > '9'))
		{
			ft_putstr_fd(
					"error: '-' must be followed only by a digit\n", 2);
			return (-1);
		}
		if (buf[i] != '-' && buf[i] != ' ' && buf[i] != '\n'\
			&& !(buf[i] >= '0' && buf[i] <= '9'))
		{
			if (buf[i] == ',' && ft_hexa(buf, i, i + 9, i) == -1)
			{
				ft_putstr_fd("error: hexadecimal error\n", 2);
				return (-1);
			}
			else
			{
				ft_putstr_fd("error: bad character in file\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

char		*ft_endbuf(char *buf, int *length)
{
	int		i;

	i = 0;
	if (buf[0] == '\0')
	{
		ft_putstr_fd("error: file is empty\n", 2);
		return (NULL);
	}
	while (buf[i] != '\0')
		i++;
	buf[i - 1] = '\0';
	if (ft_start_error(buf) == -1 || ft_invalid(buf, 0) == -1)
		return (NULL);
	if ((*length = ft_length_error(buf)) == -1)
	{
		ft_putstr_fd("error: lines of the file are not the same length\n", 2);
		return (NULL);
	}
	return (buf);
}

int			**ft_newtab(char *buf, int nbl, int nbi, int j)
{
	int		i;
	int		k;
	int		**tab;

	k = 0;
	if (!(tab = (int **)malloc(sizeof(int *) * nbl)))
		return (NULL);
	while (buf[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(tab[j] = (int *)malloc(sizeof(int) * nbi)))
			return (NULL);
		while (buf[k] != '\n' && buf[k] != '\0' && j < nbl)
		{
			tab[j][i++] = ft_atoi(buf, &k);
			while (buf[k] == ' ')
				k++;
		}
		k++;
		j++;
	}
	return (tab);
}

static void	ft_indicate_error(char *file)
{
	char	*message;

	message = ft_strnew(1);
	message = ft_strjoin(message, "error: ");
	message = ft_strjoin(message, strerror(errno));
	message = ft_strjoin(message, " for ");
	message = ft_strjoin(message, file);
	message = ft_strjoin(message, "\n");
	ft_putstr_fd(message, 2);
}

int	ft_start(char *argv, int argc, int *fd)
{
	if (argc != 2)
	{
		ft_putstr_fd("usage: ./FdF input_file\n", 2);
		return (-1);
	}
	if (BUFF_SIZE < 1)
	{
		ft_putstr_fd("error: BUFF_SIZE must be greater than 0\n", 2);
		return (-1);
	}
	if ((*fd = open(argv, O_RDONLY)) == -1)
	{
		ft_indicate_error(argv);
		return (-1);
	}
	return (1);
}



int			main(int argc, char **argv)
{
	int		nbl;
	int		nbi;
	int		fd;
	char	*line;
	char	*buf;

	nbl = 0;
	buf = ft_strnew(1);
	if (ft_start(argv[1], argc, &fd) == -1)
		return (0);
	while (get_next_line(fd, &line) > 0 && nbl++ > -1)
		buf = ft_strjoin(ft_strjoin(buf, line), "\n");
	if (get_next_line(fd, &line) != 0)
	{
		ft_putstr_fd("error: get_next_line returned -1\n", 2);
		free(buf);
		return (0);
	}
	if (ft_endbuf(buf, &nbi) != NULL)
		ft_init_struct(buf, nbl, nbi);
	if (close(fd) == -1)
		ft_indicate_error(argv[1]);
	return (0);
}












/*

typedef struct s_3d2
{
    float x[TAILLE];
    float y[TAILLE];
    float z[TAILLE];

}           t_3d2;



t_3d2   conv2to3(t_env *e)
{
    t_3d2 coord;
    int i  = 0;
    coord.z[0] = 0;
    coord.z[1] = 0;
    coord.z[2] = 0;
    coord.z[3] = 1;
    coord.z[4] = 1;
    coord.z[5] = 1;
    coord.z[6] = 1;
    coord.z[7] = 0;
    coord.z[8] = 0;
    coord.z[9] = 0;


    while (i < TAILLE)
    {
        coord.x[i] = (e->x[i] - 1) / sqrtf(2);
       // coord.y[i] = ((1 / sqrtf(6)) *(e->y[i] + e->x[i]));
        //coord.x[i] = e->x[i];
        coord.y[i] =  (e->x[i] + 2 * e->y[i] + 1) / sqrtf(6);


        printf("x = %f y = %f z = %f\n ", coord.x[i], coord.y[i], coord.z[i]);
        i++;
     }
     
    
     
    return(coord);
}


void    draw(void *mlx, void *win, float x, float y, int color)
{
    int i;
    int j;
    i = (int)x;
    j = (int)y;
    mlx_pixel_put(mlx, win, i, j, 0x008000);
}

void    draw_map(float *x, float *y, void *mlx, void *win, int color)
{
    int i = 0;
    int j = 1;
    int k  = 0;
    
    while (j <= TAILLE)
    {
        while (i <= TAILLE)
        {
        draw_between(x[i] , y[i], x[j], y[i], mlx, win, color); 
        draw_between(x[j] , y[i], x[j], y[j], mlx, win, color); 
        draw_between(x[j] , y[j], x[i], y[j], mlx, win, color); 
        draw_between(x[i] , y[j], x[i], y[i], mlx, win, color); 
        i++;
        }
        j++; 
        i = 0;
    }
          
  
    
}

void    draw_linee( int x1, int y0,int x0, int y1, void*mlx, void*win, int color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    dx = abs(x1 - x0);
    dx = abs(y1 - y0);
    sx = x0 < x1 ? 1 : -1;
    sy = y0 < y1 ? 1 : -1;
    err = dx + dy;

    while (4)
    {
        draw(mlx, win, x1, y1, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

int     expose_hook(t_env *e)
{

    int i = 0;
    t_3d2 c = conv2to3(e);

    draw_map( e->x,  e->y, e->mlx, e->win, e->color);
    
    return(0);
}


int     key_hook(int keycode, t_env *e)
{
    printf("key event %d\n", keycode);
    if(keycode == 53)
    {
        exit(0);
    }
    return(0);
}

int     main()
{

    t_env e;
    int i = 0;
    int j = 10;
   
    while (i <= TAILLE)
    {  
        e.y[i] = j;
        e.x[i] = j;
        
        i++;
        j += 20;
    }
    


     
    e.mlx = mlx_init();
    e.win = mlx_new_window(e.mlx, 2080, 2080, "mlx42");
    mlx_key_hook(e.win, key_hook, &e);
    mlx_expose_hook(e.win, expose_hook, &e);
    mlx_loop(e.mlx); 
    return (0);
}
*/