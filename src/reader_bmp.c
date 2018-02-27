/*
** main.c for main in /home/swaz/Epitech/Graphical/raytracer2/read_files/src/
**
** Made by Melvin Nalepka
** Login   <nalepk_m@epitech.eu>
**
** Started on  Wed Apr 26 23:00:49 2017 Melvin Nalepka
** Last update Fri May 26 15:20:57 2017 Lucas Benkemoun
*/

# include "line.h"

sfColor		get_pixel_bmp(t_bmp *bmp, int x, int y)
{
  if (x >= bmp->w || y >= bmp->h)
    return (sfYellow);
  if (x < 0 || y < 0)
    return (sfMagenta);
  return (bmp->image[y][x]);
}

void		display_bmp(t_bmp *bmp, t_my_framebuffer *framebuffer,
			    int x, int y)
{
  int		j;
  int		i;

  j = y - 1;
  while (++j < bmp->h)
    {
      i = x - 1;
      while (++i < bmp->w)
	my_put_pixel(framebuffer, i, j, bmp->image[j][i]);
    }
}

t_bmp		*get_image2(t_bmp *bmp, char *buffer)
{
  int		x;
  int		y;
  int		i;
  int		pitch;

  pitch = calcul_pitch(bmp->w);
  y = bmp->h;
  i = bmp->offset;
  while (--y > 0)
    {
      x = -1;
      while (++x < bmp->w)
	{
	  bmp->image[y][x].r = buffer[i + 2];
	  bmp->image[y][x].g = buffer[i + 1];
	  bmp->image[y][x].b = buffer[i];
	  bmp->image[y][x].a = 255;
	  i += 3;
	}
      i += pitch;
    }
  return (bmp);
}

t_bmp		*get_image(char *path, t_bmp *bmp, t_rbmp *rbmp)
{
  char		*buffer;
  int		fd;
  int		ret;

  if (rbmp->image_length == 0)
    rbmp->image_length = (rbmp->height * rbmp->width) * 3
      + ((rbmp->height * calcul_pitch(rbmp->width)));
  if (((buffer = malloc(sizeof(char) * rbmp->image_length)) == NULL)
      || ((fd = open(path, O_RDONLY)) == -1)
      || ((ret = (read(fd, buffer, rbmp->image_length))) < 0))
    return (NULL);
  buffer[ret - 1] = 0;
  bmp->h = rbmp->height;
  bmp->w = rbmp->width;
  bmp = get_image2(bmp, buffer);
  if (close(fd) == -1)
    return (NULL);
  return (bmp);
}

t_bmp		*read_bmp(char *path)
{
  int		fd;
  int		nb_read;
  int		y;
  t_rbmp	*rbmp;
  t_bmp		*bmp;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((rbmp = malloc(sizeof(t_rbmp))) == NULL)
    return (NULL);
  if ((nb_read = read(fd, rbmp, sizeof(t_rbmp))) < 0)
    return (NULL);
  if (close(fd) == -1)
    return (NULL);
  if ((bmp = malloc(sizeof(t_bmp))) == NULL)
    return (NULL);
  if ((bmp->image = malloc(sizeof(sfColor *) * rbmp->height)) == NULL)
    return (NULL);
  y = -1;
  while (++y < rbmp->height)
    if ((bmp->image[y] = malloc(sizeof(sfColor) * rbmp->width)) == NULL)
	return (NULL);
  bmp->offset = rbmp->offset;
  bmp = get_image(path, bmp, rbmp);
  return (bmp);
}
