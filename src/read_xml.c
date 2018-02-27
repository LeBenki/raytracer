/*
** read_xml.c for raytracer1 in /home/benki/Epitech/raytracer1
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Mon Mar 13 17:43:54 2017 Lucas Benkemoun
** Last update Sun May 28 14:23:36 2017 Lucas Benkemoun
*/

#include "line.h"

static int	my_malloc_struc(t_ray *ray)
{
  if ((!(ray->cos_angle = malloc(sizeof(float) * ray->n))) ||
      (!(ray->texture = malloc(sizeof(t_bmp *) * ray->n))))
    return (1);
  if ((!(ray->color = malloc(sizeof(sfColor) * ray->n))) ||
      (!(ray->k = malloc(sizeof(float) * ray->n))))
    return (1);
  if ((!(ray->form = malloc(sizeof(char) * ray->n))) ||
      (!(ray->radius = malloc(sizeof(float) * ray->n))))
    return (1);
  if (!(ray->noise = malloc(sizeof(float) * ray->n)))
    return (1);
  if (!(ray->pos = malloc(sizeof(sfVector3f) * ray->n)))
    return (1);
  if (!(ray->rot = malloc(sizeof(sfVector3f) * ray->n)))
    return (1);
  if ((!(ray->shadow = malloc(sizeof(float) * ray->n))) ||
      (!(ray->limit = malloc(sizeof(sfVector3f) * ray->n))))
    return (1);
  if ((!(ray->refl = malloc(sizeof(float) * ray->n))) ||
      (!(ray->color_refl = malloc(sizeof(sfColor) * ray->n))))
    return (1);
  if ((!(ray->trans = malloc(sizeof(float) * ray->n))) ||
      (!(ray->color_trans = malloc(sizeof(sfColor) * ray->n))))
    return (1);
  return (0);
}

void	init_main(char *str, t_ray *ray)
{
  if (!my_strncmp(str, "eye=", 4))
    ray->eye = init_three(str);
  (!my_strncmp(str, "dist=", 5)) ? ray->dist_toplan = init_one(str) : 0;
  if (!my_strncmp(str, "light=", 6))
    ray->light = init_three(str);
  if (!my_strncmp(str, "background=", 11))
    ray->background = read_bmp(&str[11]);
  (!my_strncmp(str, "width=", 6)) ? ray->width = init_one(str) : 0;
  (!my_strncmp(str, "expor=", 6)) ? ray->expor = (int)init_one(str) : 0;
  (!my_strncmp(str, "filtre=", 7)) ? ray->filtre = (int)init_one(str) : 0;
  (!my_strncmp(str, "threads=", 8)) ? ray->threads = (int)init_one(str) : 0;
  (!my_strncmp(str, "AA=", 3)) ? ray->AA = (int)init_one(str) : 0;
  (!my_strncmp(str, "height=", 7)) ? ray->height = init_one(str) : 0;
  (!my_strncmp(str, "lum=", 4)) ? ray->lum = init_one(str) : 0;
  if (!my_strncmp(str, "eyerot=", 7))
    ray->eyerot = init_three(str);
  (!my_strncmp(str, "brillance=", 10)) ? ray->brillance = init_one(str) : 0;
  if (!my_strncmp(str, "colorlight=", 11))
    ray->colorlight = init_color(str);
  if (!my_strncmp(str, "n=", 2))
    {
      ray->n = my_getnbr(&str[2]);
      my_malloc_struc(ray);
      init_limit(ray);
    }
}

int	init_form(char *str, t_ray *ray, int n)
{
  (!my_strncmp(str, "<sphere>", 8)) ? ray->form[n] = 's' : 0;
  (!my_strncmp(str, "<plan>", 6)) ? ray->form[n] = 'p' : 0;
  (!my_strncmp(str, "<cone>", 6)) ? ray->form[n] = 'c' : 0;
  (!my_strncmp(str, "<cylindre>", 10)) ? ray->form[n] = 'y' : 0;
  (!my_strncmp(str, "<paraboloide>", 13)) ? ray->form[n] = 'a' : 0;
  (!my_strncmp(str, "<hyperboloide>", 14)) ? ray->form[n] = 'h' : 0;
  if (!my_strncmp(str, "color=", 6))
    ray->color[n] = init_color(str);
  if (!my_strncmp(str, "radius=", 7) || !my_strncmp(str, "effet=", 6))
    ray->radius[n] = init_one(str);
  if (!my_strncmp(str, "texture=", 8))
    ray->texture[n] = read_bmp(&str[8]);
  if (!my_strncmp(str, "pos=", 4))
    ray->pos[n] = init_three(str);
  if (!my_strncmp(str, "rot=", 4))
    ray->rot[n] = init_three(str);
  if (!my_strncmp(str, "limit=", 6))
    ray->limit[n] = init_three(str);
  (!my_strncmp(str, "trans=", 6)) ? ray->trans[n] = init_one(str) : 0;
  (!my_strncmp(str, "noise=", 6)) ? ray->noise[n] = init_one(str) : 0;
  (!my_strncmp(str, "refl=", 5)) ? ray->refl[n] = init_one(str) : 0;
  return (0);
}

static void	init_all(char **tab, t_ray *ray)
{
  int		i;
  int		n;

  n = i = ray->n = 0;
  ray->background = NULL;
  ray->width = 800;
  ray->height = 600;
  ray->lum = ray->brillance = 1;
  ray->expor = 0;
  ray->AA = ray->filtre = 0;
  ray->threads = 1;
  ray->colorlight = set_color(255, 255, 255, 255);
  if (!my_strncmp(tab[i], "<xml>", 5))
    i += 1;
  if (!my_strncmp(tab[i], "<main>", 6))
    while (tab[++i] && my_strncmp(tab[i], "</main>", 7))
      init_main(tab[i], ray);
  i++;
  while (tab[i] && n < ray->n)
    {
      if (!my_strncmp(tab[i], "</", 2))
	n++;
      init_form(tab[i], ray, n);
      i++;
    }
}

t_ray	*read_xml(t_ray *ray, char *file)
{
  int	fd;
  int	i;
  char	*str;
  int	ret;
  char	**tab;

  i = -1;
  str = malloc(10000);
  ray->xml = file;
  if ((fd = open(file, O_RDONLY)) < 0)
    return (NULL);
  if (!(ret = read(fd, str, 10000)))
    return (NULL);
  ray->calcul = init_calcul();
  1 ? str[ret] = 0, tab = my_str_to_wordtab(str) : 0;
  free(str);
  while (tab[++i])
    tab[i] = my_epur_str(tab[i]);
  1 ? init_all(tab, ray), ray->i = 0, ray->save = ray->eye, i = -1 : 0;
  while (tab[++i])
    free(tab[i]);
  free(tab);
  (ray->threads <= 0) ? (ray->threads = 1) : 0;
  return (ray);
}
