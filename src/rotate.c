/*
** my_rotation.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Thu Feb  9 01:02:47 2017 Lucas Benkemoun
** Last update Sun May 28 19:37:41 2017 Melvin Nalepka
*/

#include "line.h"

static sfVector3f	rx(sfVector3f *vect, double x)
{
  sfVector3f		tmp;

  tmp.x = vect->x;
  tmp.y = vect->y * cos(x) - vect->z * sin(x);
  tmp.z = vect->y * sin(x) + vect->z * cos(x);
  return (tmp);
}

static sfVector3f	ry(sfVector3f *vect, double y)
{
  sfVector3f		tmp;

  tmp.x = vect->x * cos(y) + vect->z * sin(y);
  tmp.y = vect->y;
  tmp.z = vect->x * -sin(y) + vect->z * cos(y);
  return (tmp);
}

static sfVector3f	rz(sfVector3f *vect, double z)
{
  sfVector3f		tmp;

  tmp.x = vect->x * cos(z) - vect->y * sin(z);
  tmp.y = vect->x * sin(z) + vect->y * cos(z);
  tmp.z = vect->z;
  return (tmp);
}

sfVector3f		rotate_xyz(sfVector3f vect, sfVector3f rot)
{
  rot.x = rot.x / (180 / M_PI);
  rot.y = rot.y / (180 / M_PI);
  rot.z = rot.z / (180 / M_PI);
  vect = rx(&vect, rot.x);
  vect = ry(&vect, rot.y);
  vect = rz(&vect, rot.z);
  return (vect);
}

sfVector3f		rotate_zyx(sfVector3f vect, sfVector3f rot)
{
  rot.x = rot.x / (180 / M_PI);
  rot.y = rot.y / (180 / M_PI);
  rot.z = rot.z / (180 / M_PI);
  vect = rz(&vect, rot.z);
  vect = ry(&vect, rot.y);
  vect = rx(&vect, rot.x);
  return (vect);
}
