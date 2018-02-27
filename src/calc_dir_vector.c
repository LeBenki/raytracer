/*
** calc_dir_vector.c for bootstrap in /home/benki/Epitech/bsraytracer1
** 
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
** 
** Started on  Tue Feb  7 17:35:50 2017 Lucas Benkemoun
** Last update Fri Feb 24 11:51:58 2017 Lucas Benkemoun
*/

#include "line.h"

sfVector3f	calc_dir_vector(float dist_to_plane,
				sfVector2i screen_size, sfVector2i screen_pos)
{
  sfVector3f	vector;

  vector.x = dist_to_plane;
  vector.y = screen_size.x / 2 - screen_pos.x;
  vector.z = screen_size.y / 2 - screen_pos.y;
  return (vector);
}
