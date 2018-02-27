/*
** cluster.c for raytracer2 in /home/mpiuser/rt2_cluster
**
** Made by Baptiste Coudoulet
** Login   <baptiste.coudoulet@epitech.eu>
**
** Started on  Sat May 27 23:13:16 2017 Baptiste Coudoulet
** Last update Sun May 28 14:29:23 2017 root
*/

#include "line.h"

void		id_print(t_mpi mpi)
{
  if (!mpi.world_rank)
    {
      printf(YELLOW_BOLD "--- Master ---\n" RESET);
      printf("The master %s watch.\n", mpi.processor_name);
    }
  else
    {
      printf(RED_BOLD "--- Slave ---\n" RESET);
      printf("Hello world from processor %s, rank %d, out of %d processor\n",
	     mpi.processor_name, mpi.world_rank, mpi.world_size);
    }
}

t_ray		*choose_form_color(t_ray *ray, float *save,
				   int *col, int *bool_dark)
{
  while (ray->count < ray->n)
    {
      if (ray->k[ray->count] < *(save) && ray->k[ray->count] > 0)
	{
	  *(save) = ray->k[ray->count];
	  *(col) = ray->count;
	  *(bool_dark) = 0;
	}
      ray->count++;
    }
  return (ray);
}

t_pixel		my_cluster_compare(t_ray *ray, t_pixel pixel, MPI_Datatype type)
{
  float		save;
  int		col;
  int		bool_dark;
  sfColor	color;

  ray->count = 0;
  save = 60000000;
  col = -1;
  bool_dark = 1;
  pixel.i = ray->i;
  pixel.j = ray->j;
  ray = choose_form_color(ray, &save, &col, &bool_dark);
  if (bool_dark && !ray->background)
    color = sfBlack;
  else if (bool_dark)
    color = get_pixel_bmp(ray->background,
			  (ray->j * ray->background->w) / ray->width ,
			  (ray->i * ray->background->h) / ray->height);
  else
    color = cal_col(ray->color[col], ray->cos_angle[col], ray, col);
  pixel = color_to_pixel(pixel, color);
  MPI_Send(&pixel, 1, type, 0, 0, MPI_COMM_WORLD);
  return (pixel);
}

void		slave(t_mpi mpi, t_ray *ray, MPI_Datatype type,
		      t_my_framebuffer *fb)
{
  t_pixel	pixel;

  id_print(mpi);
  mpi.origin = (ray->width / (mpi.world_size - 1)) * (mpi.world_rank - 1);
  mpi.limit = mpi.origin + (ray->width / (mpi.world_size - 1));
  while (++ray->i < ray->height)
    {
      ray->j = mpi.origin - 1;
      while (++ray->j < ray->width && ray->j < mpi.limit)
	{
	  ray->count = -1;
	  while (++ray->count < ray->n)
       	    {
       	      my_reset(ray);
	      ray->dir_vector = calc_dir_vector(ray->dist_toplan,
						set_vector(ray->width, ray->height),
						set_vector(ray->j, ray->i));
       	      my_eye_rotate(ray);
       	      calcul(ray);
       	    }
	  pixel = my_cluster_compare(ray, pixel, type);
	  running_display(fb, pixel);
	}
    }
  MPI_Send(0, 0, MPI_INT, 0, DIETAG, MPI_COMM_WORLD);
}

void			master(t_mpi mpi, MPI_Datatype type, t_my_framebuffer *fb)
{
  MPI_Status		status;
  t_pixel		pixel;
  int			nb;

  id_print(mpi);
  nb = 1;
  while (1)
    {
      MPI_Recv(&pixel, 1, type, MPI_ANY_SOURCE, MPI_ANY_TAG,
	       MPI_COMM_WORLD, &status);
      running_display(fb, pixel);
      if (status.MPI_TAG == DIETAG)
	{
	  nb ++;
	  if (nb >= mpi.world_size)
	    break;
	}
    }
}
