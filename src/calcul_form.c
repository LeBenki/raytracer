/*
** calcul_form.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat May 27 10:55:26 2017 Lucas Benkemoun
** Last update Sun May 28 11:22:01 2017 Lucas Benkemoun
*/

#include "line.h"

void		calcul_plan(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_plane(ray->eye, ray->dir_vector)) < 0)
    return;
  if (calcul_shadow(ray, ray->k[ray->count], 'p') < 0)
    {
      ray->cos_angle[ray->count] = -1;
      return;
    }
  ray->cos_angle[ray->count] = draw_plane(ray);
}

void		calcul_cyl(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_cylinder(ray->eye, ray->dir_vector,
			  ray->radius[ray->count])) < 0)
    return;
  ray->cos_angle[ray->count] = draw_cyl(ray);
}

void		calcul_cone(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_cone(ray->eye, ray->dir_vector, ray->radius[ray->count])) < 0)
    return;
  if (calcul_shadow(ray, ray->k[ray->count], 'c') < 0)
    {
      ray->cos_angle[ray->count] = -1;
      return;
    }
  ray->cos_angle[ray->count] = draw_cone(ray);
}

void		calcul_hyp(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_hyperboloide(ray->eye, ray->dir_vector,
			      ray->radius[ray->count])) < 0)
    return;
  if (calcul_shadow(ray, ray->k[ray->count], 'h') < 0)
    {
      ray->cos_angle[ray->count] = -1;
      return;
    }
  ray->cos_angle[ray->count] = draw_hyperboloide(ray);
}

void		calcul_para(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_paraboloide(ray->eye, ray->dir_vector,
			     ray->radius[ray->count])) < 0)
    return;
  if (calcul_shadow(ray, ray->k[ray->count], 'a') < 0)
    {
      ray->cos_angle[ray->count] = -1;
      return;
    }
  ray->cos_angle[ray->count] = draw_paraboloide(ray);
}
