/*
** line.h for bswireframe in /home/lucas99.06/Epitech/Semester1/Graph_Prog/bswireframe
**
** Made by Lucas Benkemoun
** Login   <benke_l@epitech.net>
**
** Started on  Mon Nov 14 10:22:38 2016 Lucas Benkemoun
** Last update Thu Jun  1 10:59:06 2017 
*/

#ifndef LINE_H_
# define LINE_H_

# define FADE(t) (t * t * t * (t * (t * 6 - 15) + 10))
# define LERP(t, a, b) (a + t * (b - a))

#include <unistd.h>
#include <stdlib.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "mpi.h"
#include "struct.h"

#define RESET		"\x1b[0m"
#define CYAN_BOLD	"\x1b[36;1m"
#define YELLOW_BOLD	"\x1b[33;1m"
#define RED_BOLD	"\x1b[31;1m"
#define DIETAG		2

void			my_put_pixel(t_my_framebuffer*, int, int, sfColor);
t_bmp			*read_bmp(char *);
t_bmp			*get_image(char *, t_bmp *, t_rbmp *);
t_my_framebuffer	*my_framebuffer_create(int, int);
sfRenderWindow		*create_window(char*, int, int);
sfColor			set_color(sfUint8, sfUint8, sfUint8, sfUint8);
sfVector2i		set_vector(int, int);
sfVector2f		set_vectorf(float, float);
sfVector3f		set_vectorff(float, float, float);
sfVector3f		calc_dir_vector(float, sfVector2i, sfVector2i);
float			intersect_sphere(sfVector3f, sfVector3f, float);
float			intersect_cone(sfVector3f, sfVector3f, float);
float			intersect_cylinder(sfVector3f, sfVector3f, float);
float			intersect_plane(sfVector3f, sfVector3f);
float			get_light_coef(sfVector3f, sfVector3f);
int			process_game_loop(sfRenderWindow*, sfSprite*);
int			calcul_pitch(int);
int			start_menu(int, char **);
void			my_framebuffer_kill(t_my_framebuffer*);
float			draw_sphere(t_ray *);
float			draw_plane(t_ray *);
float			draw_cyl(t_ray *);
float			draw_cone(t_ray *);
sfVector3f		calcul_light(sfVector3f, sfVector3f);
sfVector3f		get_normal_cone(sfVector3f, float);
sfVector3f		get_normal_cylinder(sfVector3f);
sfVector3f		get_normal_sphere(sfVector3f);
sfVector3f		get_normal_plane(int);
float			get_light_coef(sfVector3f, sfVector3f);
sfVector3f		rotate_xyz(sfVector3f, sfVector3f);
sfVector3f		rotate_zyx(sfVector3f, sfVector3f);
sfVector3f		translate(sfVector3f, sfVector3f);
float			intersect_paraboloide(sfVector3f, sfVector3f, float);
float			draw_paraboloide(t_ray *);
float			intersect_hyperboloide(sfVector3f, sfVector3f, float);
float			draw_hyperboloide(t_ray *);
void			my_reset(t_ray *);
sfVector3f		calcul_light(sfVector3f, sfVector3f);
sfColor			cal_col(sfColor, float, t_ray *, int);
void			calcul(t_ray *);
t_ray			*read_xml(t_ray *, char *);
void			my_showtab(char **);
int			my_strlen(char *);
char			**my_str_to_wordtab(char *);
int			my_strncpy(char *, char *, int);
int			my_getnbr(char *);
int			my_strncmp(char *, char *, int);
char			*my_epur_str(char *);
sfColor			init_color(char *);
sfVector3f		init_three(char *);
float			init_one(char *);
float			calcul_shadow(t_ray *, float, char);
float			my_getfloat(char *);
sfVector2f		init_two(char *);
void			init_limit(t_ray *);
void			my_form_rotate(t_ray *);
void			my_eye_rotate(t_ray *);
sfVector3f		my_normalise(sfVector3f);
int			raytracer(int, char **);
sfColor         	get_transparence(t_ray *, sfVector3f, sfVector3f);
sfColor         	get_reflection(t_ray *, sfVector3f, sfVector3f);
float			my_find_k(sfVector3f, sfVector3f, int *, t_ray *);
sfVector3f		get_normal_paraboloide(sfVector3f, float);
sfVector3f		get_normal_hyperboloide(sfVector3f, float);
sfVector3f		test_norm(t_ray *, sfVector3f, int);
float			test_trans(t_ray *, sfVector3f, sfVector3f, int);
t_ray			*init_elipse(t_ray *);
sfColor			get_pixel_bmp(t_bmp *, int, int);
void			display_bmp(t_bmp *, t_my_framebuffer *, int, int);
void			frame_to_bmp(t_my_framebuffer *);
t_my_framebuffer	*anti_aliasing(t_my_framebuffer *, int);
void			filters(t_my_framebuffer *, int);
sfColor			my_get_color(t_my_framebuffer *, int, int);
sfColor			color_add(sfColor, sfColor);
sfColor			color_sub(sfColor, sfColor);
sfColor			color_div(sfColor, int);
t_calcul		*init_calcul();
void			calcul_cone(t_ray *ray);
void			calcul_para(t_ray *ray);
void			calcul_sphere(t_ray *ray);
void			calcul_hyp(t_ray *ray);
void			calcul_plan(t_ray *ray);
void			calcul_cyl(t_ray *ray);
sfColor			my_texture(sfVector3f, t_bmp *);
void			my_compare(t_my_framebuffer *, t_ray *);
void			thread_raytrace_scene(t_my_framebuffer *, t_ray *);
void			slave(t_mpi, t_ray *, MPI_Datatype, t_my_framebuffer *);
void			master(t_mpi, MPI_Datatype, t_my_framebuffer *);
t_mpi			init_mpi_struct(char *, int, int);
t_pixel			color_to_pixel(t_pixel, sfColor);
sfColor			pixel_to_color(t_pixel);
t_mpi			init_mpi_struct(char *, int, int);
void			running_display(t_my_framebuffer *, t_pixel);
sfVector3f		damier(t_ray *, sfVector3f, sfVector3f);
float			noise(float, float, float);
sfColor			color_table(float, float, sfColor, sfVector3f);
int			my_end(t_my_framebuffer *, sfTexture *,
			       sfSprite *, sfRenderWindow *);
int			switch_to_help(sfRenderWindow *, sfSprite *,
				       t_my_framebuffer *, sfTexture *);
int                     set_back(t_my_framebuffer *, int, sfTexture *);

#endif	/* !LINE_H_ */
