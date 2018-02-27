/*
** util_graph.c for wolf3d in /home/lucas99.06/Epitech/Semester1/Graph_Prog/wolf3d/test
**
** Made by Lucas Benkemoun
** Login   <benke_l@epitech.net>
**
** Started on  Wed Jan  4 21:10:17 2017 Lucas Benkemoun
** Last update Sun May 28 19:55:13 2017 Melvin Nalepka
*/

#include "line.h"

sfVector3f	my_normalise(sfVector3f vector)
{
  float		length;

  length = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
  vector.x /= length;
  vector.y /= length;
  vector.z /= length;
  return (vector);
}

sfColor		set_color(sfUint8 r, sfUint8 g, sfUint8 b, sfUint8 a)
{
  sfColor	color;

  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return (color);
}

sfVector3f	set_vectorff(float x, float y, float z)
{
  sfVector3f	vector;

  vector.x = x;
  vector.y = y;
  vector.z = z;
  return (vector);
}

sfVector2i	set_vector(int x, int y)
{
  sfVector2i	vector;

  vector.x = x;
  vector.y = y;
  return (vector);
}

sfVector2f	set_vectorf(float x, float y)
{
  sfVector2f	vector;

  vector.x = x;
  vector.y = y;
  return (vector);
}
