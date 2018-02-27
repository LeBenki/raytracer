/*
** light.c for raytracer1 in /home/benki/Epitech/raytracer1
** 
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
** 
** Started on  Wed Feb 15 16:03:03 2017 Lucas Benkemoun
** Last update Fri Mar 17 09:29:06 2017 Lucas Benkemoun
*/

#include "line.h"

float		get_light_coef(sfVector3f dir, sfVector3f normal)
{
  float		cos_angle;

  if (normal.x == 0 && normal.y == 0 && normal.z == 0)
    return (0);
  if (dir.x == 0 && dir.y == 0 && dir.z == 0)
    return (0);
  cos_angle = (normal.x * dir.x + normal.y * dir.y + normal.z * dir.z);
  cos_angle /= (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) *
		sqrt(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2)));
  return (cos_angle > 0 ? cos_angle : 0);
}
