/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 17:38:45 by amontano          #+#    #+#             */
/*   Updated: 2018/09/14 06:13:02 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include "libft.h"
# include "keys.h"
# include "ft_color.h"
# include "../minilibx_macos/mlx.h"
# define WIN_W 1600
# define WIN_H 912
# define HALF_W 800
# define HALF_H 456
# define TPIX 1459200
# define TMEM 5836800
# define STEP_SZ 0.06125
# define ROT_SZ (M_PI / 60)
# define MIN_WALL_DIST 0.25
# define TEX_SZ 14
# define THREADS 8
# define TEX_W	64
# define N_MAPS 3

typedef struct	s_tile
{
	int				x;
	int				y;
	int				properties;
	char			sprite;
}				t_tile;

typedef struct	s_map
{
	t_tile			***grid;
	int				id;
	int				h;
	int				w;
}				t_map;

typedef	struct	s_pc
{
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			camx;
	double			camy;
	int				angle;
	int				held[TEX_SZ];
	int				select;
	int				coin[4];
	int				wincondition;
}				t_pc;

typedef struct	s_vec
{
	double			x;
	double			y;
	int				a;
	int				b;
	double			dir;
}				t_vec;

typedef struct	s_img
{
	void			*img;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
	int				width;
	int				height;
}				t_img;

typedef struct	s_kb
{
	unsigned char	f;
	unsigned char	b;
	unsigned char	l;
	unsigned char	r;
	unsigned char	rot_l;
	unsigned char	rot_r;
	unsigned char	run;

}				t_kb;

typedef struct	s_ray
{
	double			sdy;
	double			sdx;
	double			perp;
	double			rdx;
	double			rdy;
	int				h;
	int				side;
	int				texnum;

}				t_ray;

typedef	struct	s_sprite
{
	double			x;
	double			y;
	t_img			*tex;
	t_map			*map;
}				t_sprite;

typedef struct	s_mlx
{
	void			*mlx;
	void			*win;
	t_map			**all_maps;
	t_map			*map;
	t_img			*img;
	t_img			*bg;
	t_img			*inv;
	t_kb			*kb;
	t_pc			*player;
	t_img			*tex[TEX_SZ];
	t_sprite		**sprites;
	int				n_sprites;
	t_hsv			***hsvtex;
	double			zbuf[WIN_W];
}				t_mlx;

typedef struct	s_argp
{
	t_mlx			*mlx;
	int				id;
}				t_argp;

t_img			*del_img(t_mlx *mlx, t_img *img);
void			clear_img(t_img *img);
t_img			*new_img(t_mlx *mlx);
void			img_set_pixel(t_img *img, int x, int y, int color);
int				hook_key_down(int key, t_mlx *mlx);
int				hook_key_up(int key, t_mlx *mlx);
int				hook_mouse_down(int key, int x, int y, t_mlx *mlx);
void			*manage_moves(void *mlx_ptr);
int				dispose(t_list **lst, t_map **map);
int				uldispose(char ***split);
void			error(char *str);
int				read_file(int fd, t_map **map);
t_tile			*set_tile(int x, int y, char *str);
t_pc			*init_player(t_mlx *mlx);
int				render(t_mlx *mlx);
void			draw_line(int x, t_ray *r, t_mlx *mlx);
void			shoot_ray(t_ray *ray, t_pc *pc, int x, t_argp *p);
void			draw_bg(t_mlx *mlx, int a, int b);
void			draw_inventory(t_mlx *mlx);
int				load_textures(t_mlx *mlx);
t_img			*xpm_image(char *xpm, t_mlx *mlx);
int				grab_color_from_tex(int x, int y, t_img *img);
void			rotate(t_pc *p, int dir, double rot);
void			draw_hud(t_mlx *mlx);
char			*ft_ftoa(double f, unsigned int acc);
int				grab_color_from_tex(int x, int y, t_img *img);
int				get_tex_y(t_ray *r, int y);
int				get_tex_x(t_ray *r, t_pc *p);
int				get_tile(t_map *m, int x, int y);
int				get_player_tile(t_mlx *mlx);
void			pickup(t_mlx *mlx, t_map *map);
void			drop(t_mlx *mlx, t_map *map);
void			scan_event(t_mlx *mlx);
int				is_full_map(t_map *m);
int				checkmap(t_map *m);
int				is_enclosed_map(t_map *m);
void			get_music(t_mlx *mlx);
t_sprite		**init_sprites(t_mlx *mlx);
t_img			*init_inventory(t_mlx *mlx);
void			img_put_trans(t_img *src, t_img *dest, int x, int y);
int				loop_handler(t_mlx *mlx);
void			sprite_helper(t_mlx *mlx, t_pc *p);
int				hook_close(void);
void			move_helper(t_mlx *mlx, int key);
void			strafe(t_mlx *mlx, double dir);
void			move(t_mlx *mlx, double dir);
t_img			*tex_helper(t_mlx *mlx, char *t);
void			build_inv(t_img *tex, t_img *dest, int x, int y);
void			check_hit(t_ray *r, t_argp *p, t_vec all[5]);
t_hsv			**ft_img_to_hsv(t_img *i);
void			draw_sprites(t_mlx *mlx, t_pc *p, int total);
void			get_sprite_dist(int *order, double *dist, t_mlx *mlx, t_pc *p);
void			get_sprite_data(double depth, int screenx, int *sd);
t_vec			project_sprites(t_mlx *mlx, t_pc *p, int *order, int aa);
void			draw_sprite_tex(int *sd, t_vec uv, t_mlx *mlx, int *o);
void			sprite_collision(int aa, double *dist, int *order, t_mlx *mlx);
void			update_coin(t_pc *p, char c);
void			sort_sprites_by_dist(int *order, double *dist, int n);
int				sprites_on_map(t_mlx *mlx, int n, t_sprite **all, int w);
t_sprite		*create_sprite(double x, double y, t_map *map);
void			assign_texture(char c, t_sprite *s, t_mlx *mlx);
int				count_sprites(t_map **world);
t_tile			*first_empty_tile(t_map *map);

#endif
