/*
** color_pixel.c for raytracer2 in /home/coudoul/Epitech/raytracer2/bonus
**
** Made by Baptiste Coudoulet
** Login   <baptiste.coudoulet@epitech.eu>
**
** Started on  Sun May 28 13:19:12 2017 Baptiste Coudoulet
** Last update Sun May 28 13:19:40 2017 root
*/

#include "line.h"

t_pixel		color_to_pixel(t_pixel pixel, sfColor color)
{
  pixel.r = color.r;
  pixel.g = color.g;
  pixel.b = color.b;
  pixel.a = color.a;
  return (pixel);
}

sfColor		pixel_to_color(t_pixel pixel)
{
  sfColor 	color;

  color.r = pixel.r;
  color.g = pixel.g;
  color.b = pixel.b;
  color.a = pixel.a;
  return (color);
}
