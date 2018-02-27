/*
** texture.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat May 27 09:42:07 2017 Lucas Benkemoun
** Last update Sun May 28 12:34:18 2017 Lucas Benkemoun
*/

#include "line.h"

float		produit_scalaire(sfVector3f u, sfVector3f v)
{
  return (u.x * v.x + u.y * v.y + u.z * v.z);
}

sfColor		my_texture(sfVector3f point, t_bmp *bmp)
{
  float		phi;
  sfVector3f	Vn;
  sfVector3f	Vp;
  sfVector3f	Ve;
  float		theta;
  float		u;
  float		v;

  Vp = my_normalise(point);
  Ve.x = 0;
  Ve.y = 1;
  Ve.z = 0;
  Vn.x = 0;
  Vn.y = 0;
  Vn.z = 1;
  phi = acos(-produit_scalaire(Vn, Vp));
  v = phi / M_PI;
  theta = (acos(produit_scalaire(Vp, Ve) / sin(phi))) / (2 * M_PI);
  if (produit_scalaire(set_vectorff(0, 0, 0), Vp) > 0)
    u = theta;
  else
    u = 1 - theta;
  return (get_pixel_bmp(bmp, bmp->w - u * bmp->w, bmp->h - (v * bmp->h)));
}
