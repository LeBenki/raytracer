/*
** struct.h for raytracer2 in /home/mpiuser/rt2_cluster
**
** Made by Baptiste Coudoulet
** Login   <baptiste.coudoulet@epitech.eu>
**
** Started on  Sat May 27 23:41:18 2017 Baptiste Coudoulet
** Last update Thu Jun  1 10:58:24 2017 
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include "line.h"

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

typedef struct		s_mpi
{
  char			*processor_name;
  int			world_size;
  int			world_rank;
  int			origin;
  int			limit;
}			t_mpi;

typedef struct	s_pixel
{
  int		i;
  int		j;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
}		t_pixel;

#endif
