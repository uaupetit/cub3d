/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:24:05 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 17:26:37 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../mlx-linux/mlx.h"
# include <X11/keysym.h>
// for XK_KeyCode
# include <X11/X.h>
// for KeyPress, KeyPressMask, KeyRelease, KeyReleaseMask
# include "./get_next_line.h"

typedef struct s_player {
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	plnx;
	double	plny;
}				t_player;

typedef struct s_data {
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		side;
	double	wallx;
	int		texnum;
	int		texx;
	int		texy;
	int		texwidth;
	int		texheight;
	int		drawstart;
	int		drawend;
	double	step;
	double	texpos;
	int		mapheight;
	int		mapwidth;
	int		minx;
	int		miny;
}				t_data;

typedef struct s_img {
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img;

typedef struct s_pixel {
	int	x;
	int	y;
	int	color;
	int	scale;
}				t_pixel;

typedef struct s_check {
	int	first;
	int	last;
	int	flag;
	int	size;
}				t_check;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	int			f_color;
	int			c_color;
	int			color;
	char		**map;
	t_player	p;
	t_img		*img;
	t_img		s;
	int			width;
	int			height;
	t_check		c;
	int			prev_mouse_x;
	double		mov;
	double		limit;
	double		rot;
	int			change;
	int			scale;
	t_data		data;
}				t_vars;

/*****************main*************/
int		main(int ac, char **av);
int		init_mlx(char **av, t_vars *vars);
void	init_data(t_data *data, t_vars *vars);
int		close_window(t_vars *v);

/*****************parsing*************/

			//parsing
int		parsing(char **av, t_vars *vars, int i);
int		check_extension(char **av);
int		read_map(int fd, int i, int flag);
char	**save_map(int fd, char **tab, int i);
int		check_whitespace(char *str);
void	ft_free(char **tab);

			//check_file && check_file_utils
int		check_file_content(char **tab, t_vars *vars);
int		check_f(char **tab, t_vars *vars);
int		check_no(char **tab, t_vars *vars);
int		check_color(char *str, t_vars *vars, int code, int i);
void	create_rgb(int *tab, int code, t_vars *vars);
int		check_texture(char *str, t_vars *vars, int code);
int		check_map(char **tab, t_vars *vars, int i, int j);

			//check_map && check_map_utils
int		process_cell(char **tab, t_vars *vars, int i, int j);
void	init_var(t_check *c, int flag, char **tab);
int		is_open(char **tab, int i, int j, t_check *c);
int		get_last(char *tab);
int		is_player(char c);
int		is_environment(char c);
int		tab_size(char **tab);
int		copy_map(char **tab, t_vars *vars);
void	fill_player(t_vars *vars, char c);
int		is_whitespace(char c);

			//libft
int		ft_atoi(const char *nptr);
int		ft_isdigit(char *str);

/*******************execution************/

// raycast.c
void	raycast(t_data *data, t_vars *vars);
void	get_intersection(t_data *data, t_vars *vars);
void	get_height(t_data *data, t_vars *vars, int x);
void	dda(t_data *data, t_vars *vars);

// raycast_utils.c
void	init_ray(t_data *data, t_vars *vars, int x);
void	init_step(t_data *data);

// key.c
int		key_move_ns(int keycode, t_vars *v);
int		key_move_we(int keycode, t_vars *v);
int		key_rotation(int keycode, t_vars *v);
int		key_pressed(int keycode, t_vars *v);
int		mouse_moved(int x, int y, t_vars *v);

// angle.c
double	deg2rad(double degree);
double	rotx(double dir_x, double dir_y, double radian);
double	roty(double dir_x, double dir_y, double radian);
double	clamp(double x, double lower, double upper);
void	*ft_memset(void *s, int c, size_t n);

// draw.c
void	img_pixel_put(t_img *img, int x, int y, int color);
int		img_pixel_get(t_img *img, int x, int y);
void	draw_pixel(t_data *data, t_vars *vars, int x, int y);
void	draw_minimap(t_data *data, t_vars *vars, int x, int *y);
void	draw_column(t_data *data, t_vars *vars, int x);

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_nbmots(char const *s, char c);
void	ft_free2(char **s, int i);
size_t	ft_len(const char *s, unsigned int start, char c);
void	ft_free_img(t_vars *vars, int count);

char	*ft_replace_space(const char *s, int len);
int		fs(char *s);
char	**sort_tab(char **tab, int i, int flag, int k);
int		sort_tab_utils(char **tab, int i, int k, char **tab_cpy);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_check(char const *set, char c);
void	last_lines(int fd, int *flag, char **temp);

#endif