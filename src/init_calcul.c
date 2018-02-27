/*
** init_calcul.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat May 27 10:56:16 2017 Lucas Benkemoun
** Last update Sun May 28 11:32:05 2017 Lucas Benkemoun
*/

#include "line.h"

void		calcul_sphere(t_ray *ray)
{
  if ((ray->k[ray->count] =
       intersect_sphere(ray->eye,
			ray->dir_vector, ray->radius[ray->count])) < 0)
    return;
  if (calcul_shadow(ray, ray->k[ray->count], 's') < 0)
    {
      ray->cos_angle[ray->count] = -1;
      return;
    }
  ray->cos_angle[ray->count] = draw_sphere(ray);
}

t_calcul	*init_calcul()
{
  t_calcul	*calcul;

  calcul = malloc(sizeof(t_calcul) * 7);
  calcul[0].c = 's';
  calcul[0].func = &calcul_sphere;
  calcul[1].c = 'p';
  calcul[1].func = &calcul_plan;
  calcul[2].c = 'y';
  calcul[2].func = &calcul_cyl;
  calcul[3].c = 'c';
  calcul[3].func = &calcul_cone;
  calcul[4].c = 'h';
  calcul[4].func = &calcul_hyp;
  calcul[5].c = 'a';
  calcul[5].func = &calcul_para;
  calcul[6].c = 0;
  calcul[6].func = NULL;
  return (calcul);
}
