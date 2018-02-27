/*
** threads.c for raytracer2 in /home/coudoul/Epitech/raytracer2/src/
**
** Made by Baptiste Coudoulet
** Login   <baptiste.coudoulet@epitech.eu@epitech.eu>
**
** Started on  Tue May  2 15:25:17 2017 Baptiste Coudoulet
** Last update Sun May 28 11:36:38 2017 Lucas Benkemoun
*/

#include "line.h"

#define RED		"\x1b[31;1m"
#define RESET		"\x1b[0m"

void		*thread_fonct(void *arg)
{
  t_thread_param	*param;

  param = (t_thread_param *)arg;
  param->origin = 0 + ((param->ray->width / param->ray->threads) * param->id);
  param->l = param->origin + (param->ray->width / param->ray->threads);
  while (param->ray->i < param->ray->height)
    {
      param->ray->j = param->origin - 1;
      while (++param->ray->j < param->ray->width && param->ray->j < param->l)
	{
	  param->ray->count = -1;
	  while (++param->ray->count < param->ray->n)
	    {
	      my_reset(param->ray);
	      param->ray->dir_vector = calc_dir_vector(param->ray->dist_toplan,
						       set_vector(param->fb->width, param->fb->height),
						       set_vector(param->ray->j, param->ray->i));
	      my_eye_rotate(param->ray);
	      calcul(param->ray);
	    }
	  my_compare(param->fb, param->ray);
	}
      param->ray->i++;
    }
  return (NULL);
}

t_thread_param		init_thread_param(t_my_framebuffer *fb,
					  t_ray *ray, char *xml)
{
  t_thread_param 	param;

  param.id = 0;
  param.origin = 0;
  param.ray = malloc(sizeof(*param.ray));
  param.ray = read_xml(param.ray, xml);
  param.fb = fb;
  param.count = set_vector(0, 0);
  param.l = 0;
  param.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  return (param);
  (void)ray;
}

t_thread_param		*init_tab_param(int nb_thread, t_my_framebuffer *fb,
					  t_ray *ray, char *xml)
{
  int			i;
  t_thread_param	*param;

  i = -1;
  param = malloc(sizeof(t_thread_param) * (nb_thread));
  while (++i < nb_thread)
    param[i] = init_thread_param(fb, ray, xml);
  return (param);
}

void		thread_raytrace_scene(t_my_framebuffer *fb, t_ray *ray)
{
  pthread_t		gen_thread[ray->threads];
  int			i;
  t_thread_param	*param;
  void			*ret;

  ret = 0;
  param = init_tab_param(ray->threads, fb, ray, ray->xml);
  i = -1;
  while (++i < ray->threads)
    {
      param[i].id = i;
      pthread_create(&gen_thread[i], NULL, thread_fonct, &param[i]);
    }
  i = -1;
  while (++i < ray->threads)
    pthread_join(gen_thread[i], &ret);
}
