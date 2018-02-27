/*
** main.c for raytracer2 in /home/benki/Epitech/raytracer2/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Thu Apr 13 17:05:32 2017 Lucas Benkemoun
** Last update Sun May 28 17:02:59 2017 Lucas Benkemoun
*/

#include "line.h"

MPI_Datatype	pixel_type()
{
  const int	nitems = 6;
  int		blocklengths[6] = {1, 1, 1, 1, 1, 1};
  MPI_Datatype	types[6] = {MPI_INT, MPI_INT, MPI_UNSIGNED_CHAR,
			    MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR,
			    MPI_UNSIGNED_CHAR};
  MPI_Datatype  type;
  MPI_Aint	offsets[6];

  offsets[0] = offsetof(t_pixel, i);
  offsets[1] = offsetof(t_pixel, j);
  offsets[2] = offsetof(t_pixel, r);
  offsets[3] = offsetof(t_pixel, g);
  offsets[4] = offsetof(t_pixel, b);
  offsets[5] = offsetof(t_pixel, a);
  MPI_Type_create_struct(nitems, blocklengths, offsets, types, &type);
  MPI_Type_commit(&type);
  return (type);
}

void			cluster_start(t_my_framebuffer *fb, t_ray *ray)
{
  t_mpi			mpi;
  MPI_Datatype		type;
  int			world_size;
  int			world_rank;
  char			processor_name[MPI_MAX_PROCESSOR_NAME];
  int			name_len;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Get_processor_name(processor_name, &name_len);
  mpi = init_mpi_struct(processor_name, world_size, world_rank);
  type = pixel_type();
  if (world_rank == 0)
    master(mpi, type, fb);
  else
    slave(mpi, ray, type, fb);
  MPI_Finalize();
}

int			cluster(int ac, char **av)
{
  sfRenderWindow        *window;
  sfTexture             *texture;
  sfSprite              *s;
  t_my_framebuffer      *fb;
  t_ray                 *ray;

  if (ac != 2 && write(2, "Usage :  ./raytracer [file.xml]\n", 32))
    return (84);
  if ((!(ray = malloc(sizeof(*ray)))) || (!(ray = read_xml(ray, av[1]))))
    return (84);
  if (!(window = create_window("Raytracer 2", ray->width, ray->height)))
    return (84);
  if (!(texture = sfTexture_create(ray->width, ray->height)))
    return (84);
  1 ? s = sfSprite_create(), sfSprite_setTexture(s, texture, sfTrue) : 0;
  fb = my_framebuffer_create(ray->width, ray->height);
  1 ? fb->texture = texture, fb->window = window, fb->s = s : 0;
  cluster_start(fb, ray);
  fb = anti_aliasing(fb, ray->AA);
  filters(fb, ray->filtre);
  if (ray->expor == 1)
    frame_to_bmp(fb);
  sfTexture_updateFromPixels(texture, fb->pixels, fb->width, fb->height, 0, 0);
  process_game_loop(window, s);
  return (my_end(fb, texture, s, window));
}

int			main(int ac, char **av)
{
  return (cluster(ac, av));
}
