
# include "./libft/libft.h"
# include <errno.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

#define UP 126
#define DOWN 125
#define LEFT 123
#define RIGHT 124
#define ESC 53
#define CORTEX 12
#define MINUS 13
#define ADD_D 14
#define RM_D 15


  
typedef struct	s_env
{
    int     Color;
    int     reso;
	void		*mlx;
	void		*win;
	int			l;
	int			i;
	int			length;
	int			zoom;
	int			xmove;
	int			ymove;
	float		z;
	int			**tab;
	float		x;
	float		y;
	float		x0;
	float		x1;
	float		y0;
	float		y1;
}				t_env;
  


void	draw_between(t_env *e);
void	draw_col(t_env *e, int j, int i);
void	draw_line(t_env *e, int j, int i);
int		draw_map(t_env *e);
int			ft_init_struct(char *buf, int nbl, int nbi, int i);
int	ft_hexa(char *buf, int i, int num, int start);
int	ft_length_error(char *buf);
int	ft_start_error(char *buf);
int	ft_invalid(char *buf, int i);
char		*et_endbuf(char *buf, int *length);
int			ft_expose_hook(t_env *e);
int	ft_key_hook2(int keycode, t_env *e);
int	ft_key_hook3(int keycode, t_env *e);
int	    ft_key_hook(int keycode, t_env *e);
int			**ft_newtab(char *buf, int nbl, int nbi, int j);
void	ft_indicate_error(char *eile);
int	ft_start(char *argv, int argc, int *ed);







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
		mlx_pixel_put(e->mlx, e->win, e->x + e->xmove,\
				e->y + e->ymove, e->Color);
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
	e->y0 = (((e->reso / 2)+ (j * e->zoom)) * 1. / 2.) - (((i * e->zoom)
				+ (e->z * e->tab[j][i])) * 1. / 2.);
	e->y1 = (((e->reso / 2) + ((j + 1) * e->zoom)) * 1. / 2.) - (((i * e->zoom)
                + (e->z * e->tab[j + 1][i])) * 1. / 2.);
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

int			ft_init_struct(char *buf, int nbl, int nbi, int i)
{
	t_env	e;

    e.Color = i;
    e.z = 2.0;
	e.xmove = 0;
	e.ymove = 0;
	e.tab = ft_newtab(buf, nbl, nbi, 0);
	e.l = nbl;
	e.i = nbi;
	if (e.l >= e.i)
		e.zoom = 400 / e.l;
	else
		e.zoom = 400 / e.i;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.reso = 800, e.reso = 800, "fdf");
	mlx_expose_hook(e.win, &ft_expose_hook, &e);
	mlx_key_hook(e.win, &ft_key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

  int	ft_hexa(char *buf, int i, int num, int start)
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

  int	ft_length_error(char *buf)
{
	t_env e;

	e.i = 0;
	e.length = -1;
	while (buf[e.i] != '\0')
	{
		e.l = 0;
		while (buf[e.i] == ' ')
			e.i++;
		while (buf[e.i] != '\n' && buf[e.i] != '\0')
		{
			while (buf[e.i] == ' ' && buf[e.i] != '\n' && buf[e.i] != '\0')
				e.i++;
			if (buf[e.i] != '\n' && buf[e.i] != '\0')
				e.l++;
			while (buf[e.i] != ' ' && buf[e.i] != '\n' && buf[e.i] != '\0')
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

  int	ft_start_error(char *buf)
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

  int	ft_invalid(char *buf, int i)
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

int			ft_expose_hook(t_env *e)
{

    
    mlx_string_put(e->mlx, e->win, 55, 750, e->Color, "End with esc | Keyboard arrows to Move \
    | Zoom with Q W | Depth with E R");
	draw_map(e);
	return (0);
}

  int	ft_key_hook2(int keycode, t_env *e)
{
	if (keycode == ADD_D)
	{
		if (e->z <= 30.)
			e->z += 0.1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == RM_D)
	{
		if (e->z >= -30.)
			e->z -= 0.1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
    }
	return (0);
}

  int	ft_key_hook3(int keycode, t_env *e)
{
	if (keycode == UP)
	{
		e->ymove -= 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == CORTEX)
	{
		if (e->zoom <= 95)
			e->zoom += 1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == MINUS)
	{
		if (e->zoom >= -35)
			e->zoom -= 1;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	ft_key_hook2(keycode, e);
	return (0);
}

int			ft_key_hook(int keycode, t_env *e)
{
    printf("key event %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)
	{
		e->xmove -= 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == RIGHT)
	{
		e->xmove += 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	if (keycode == DOWN)
	{
		e->ymove += 30;
		mlx_clear_window(e->mlx, e->win);
		ft_expose_hook(e);
	}
	ft_key_hook3(keycode, e);
	return (0);
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

  void	ft_indicate_error(char *file)
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
	if (argc > 3 )
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
int     which_color(char *c)
{
    int i;

    if (ft_strcmp(c, "Blanc") == 0 || c == NULL)
        return (i = 0xFFFFFF);
    if (ft_strcmp(c, "Rouge") == 0)
        return (i = 0x00FF7F7);
    if (ft_strcmp(c, "Bleu") == 0)
        return (i = 0x0000FF);
    if (ft_strcmp(c, "Jaune") == 0)
        return (i = 0xFFFF00);
    if (ft_strcmp(c, "Vert") == 0)
        return (i = 0x008000);
    if (ft_strcmp(c, "Violet") == 0)
        return (i = 0x8A2BE2);
    if (ft_strcmp(c, "Orange") == 0)
        return (i = 0xFF3300);
    if (ft_strcmp(c, "Cyan;") == 0)
        return (i = 0x00CCFF);
    if (ft_strcmp(c, "Marron") == 0)
        return (i = 0x996600);
    return (0);

}
int			main(int argc, char **argv)
{
	int		nbl;
	int		nbi;
	int		fd;
	char	*line;
    char	*buf;
    int i;

    if (argv[2] != NULL)
        {
            i = which_color(argv[2]);
        }
    else
        i = 0xFFFFFF;
    ft_putstr_fd(argv[2], 2);
    printf("test");
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
		ft_init_struct(buf, nbl, nbi, i);
	if (close(fd) == -1)
		ft_indicate_error(argv[1]);
	return (0);
}