/*
** translate.c for raytracer1 in /home/benki/Epitech/raytracer1
** 
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
** 
** Started on  Wed Feb 15 18:03:42 2017 Lucas Benkemoun
** Last update Wed Feb 15 18:09:06 2017 Lucas Benkemoun
*/

#include "line.h"

sfVector3f	translate(sfVector3f vec, sfVector3f trans)
{
  vec.x += trans.x;
  vec.y += trans.y;
  vec.z += trans.z;
  return (vec);
}
