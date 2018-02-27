/*
** line.h for bswireframe in /home/lucas99.06/Epitech/Semester1/Graph_Prog/bswireframe
**
** Made by Lucas Benkemoun
** Login   <benke_l@epitech.net>
**
** Started on  Mon Nov 14 10:22:38 2016 Lucas Benkemoun
** Last update Sun May 28 17:00:42 2017 Lucas Benkemoun
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

typedef struct          s_my_framebuffer
{
  sfUint8*              pixels;
  int                   width;
  int                   height;
  sfRenderWindow        *window;
  sfTexture             *texture;
  sfSprite              *s;
}                       t_my_framebuffer;

#pragma pack(1)
typedef struct  s_rbmp
{
  unsigned char type[2];
  int           length;
  short         reserved1;
  short         reserved2;
  int           offset;
  int           length_head;
  int           width;
  int           height;
  short         plans;
  short         bpp;
  int           compression;
  int           image_length;
  int           Hresolution;
  int           Vresolution;
  int           nb_color;
  int           nb_main_color;
}               t_rbmp;
#pragma pack(0)

typedef struct	s_v
{
  float		f;
  sfColor	color;
}		t_v;

typedef	struct	s_bmp
{
  int		w;
  int		h;
  int		offset;
  sfColor	**image;
}		t_bmp;

typedef struct s_ray t_ray;

typedef struct		s_calcul
{
  char			c;
  void			(*func)(t_ray *);
}			t_calcul;

typedef struct          s_thread_param
{
  int                   id;
  int                   origin;
  t_my_framebuffer      *fb;
  t_ray                 *ray;
  sfTexture             *texture;
  sfVector2i            count;
  int                   l;
  pthread_mutex_t       mutex;
}			t_thread_param;

typedef struct          s_ray
{
  t_bmp			*background;
  t_bmp			**texture;
  sfVector3f		light;
  sfVector3f		eyerot;
  float			dist_toplan;
  sfVector3f		dir_vector;
  sfVector3f		eye;
  sfVector3f		point;
  char			*xml;
  int			threads;
  int			i;
  int			j;
  int			filtre;
  sfVector3f		shadow_l;
  sfVector3f		shadow_p;
  int			count;
  char			*form;
  sfVector3f		save;
  float			*k;
  float			*shadow;
  float			*noise;
  sfVector3f	       	*pos;
  float			*radius;
  float			*refl;
  float			*trans;
  float			*cos_angle;
  sfColor		*color;
  sfColor		*color_refl;
  sfColor		*color_trans;
  sfVector3f		*rot;
  int			n;
  int			expor;
  int			width;
  int			height;
  float			lum;
  float			brillance;
  sfColor		colorlight;
  sfVector3f		*limit;
  sfColor		test;
  int			AA;
  t_calcul		*calcul;
}                       t_ray;

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
void			calcul_cone(t_ray *);
void			calcul_para(t_ray *);
void			calcul_sphere(t_ray *);
void			calcul_hyp(t_ray *);
void			calcul_plan(t_ray *);
void			calcul_cyl(t_ray *);
sfColor			my_texture(sfVector3f, t_bmp *);
void			my_compare(t_my_framebuffer *, t_ray *);
void			thread_raytrace_scene(t_my_framebuffer *, t_ray *);
sfVector3f		damier(t_ray *, sfVector3f, sfVector3f);
float			noise(float, float, float);
sfColor			color_table(float, float, sfColor, sfVector3f);
int			my_end(t_my_framebuffer *, sfTexture *,
			       sfSprite *, sfRenderWindow *);
int			switch_to_help(sfRenderWindow *, sfSprite *,
				       t_my_framebuffer *, sfTexture *);
int                     set_back(t_my_framebuffer *, int, sfTexture *);

#endif	/* !LINE_H_ */
