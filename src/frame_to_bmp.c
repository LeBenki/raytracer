/*
** frame_to_bmp.c for frame_to_bmp in /home/swaz/Epitech/Graphical/raytracer2/src/
**
** Made by Melvin Nalepka
** Login   <nalepk_m@epitech.eu>
**
** Started on  Mon May 22 12:29:59 2017 Melvin Nalepka
** Last update Wed May 24 22:39:49 2017 Melvin Nalepka
*/

#include "line.h"

int		calcul_pitch(int width)
{
  char		corrpitch[4];
  int		pitch;

  corrpitch[0] = 0;
  corrpitch[1] = 3;
  corrpitch[2] = 2;
  corrpitch[3] = 1;
  pitch = corrpitch[(3 * width) % 4];
  return (pitch);
}

t_rbmp		*header_maker(t_my_framebuffer *frame, int pitch)
{
  t_rbmp	*header;

  header = NULL;
  if ((header = malloc(sizeof(t_rbmp))) == NULL)
    return (NULL);
  header->type[0] = 'B';
  header->type[1] = 'M';
  header->reserved1 = 0;
  header->reserved2 = 0;
  header->offset = 54;
  header->length_head = 40;
  header->width = frame->width;
  header->height = frame->height;
  header->plans = 1;
  header->bpp = 24;
  header->compression = 0;
  header->image_length = (frame->height * frame->width) * 3
      + (frame->height * pitch);
  header->length = header->offset + header->image_length;
  header->Hresolution = 2834;
  header->Vresolution = 2834;
  header->nb_color = 0;
  header->nb_main_color = 0;
  return (header);
}

sfColor		get_pixel(t_my_framebuffer *frame, int x, int y)
{
  sfColor	res;

  res.r = frame->pixels[(frame->width * y + x) * 4];
  res.g = frame->pixels[(frame->width * y + x) * 4 + 1];
  res.b = frame->pixels[(frame->width * y + x) * 4 + 2];
  res.a = frame->pixels[(frame->width * y + x) * 4 + 3];
  return (res);
}

void		frame_to_array(t_my_framebuffer *frame, int fd, int pitch)
{
  sfColor	tmp;
  unsigned char	bgrp[3];
  int		j;
  int		i;

  j = -1;
  while (++j < frame->height)
    {
      i = 0;
      while (i < (frame->width))
	{
	  tmp = get_pixel(frame, i, frame->height - j);
	  i++;
	  bgrp[0] = tmp.b;
	  bgrp[1] = tmp.g;
	  bgrp[2] = tmp.r;
	  if (write(fd, &bgrp, 3) == -1)
	    return ;
	}
      bgrp[0] = 0;
      bgrp[1] = 0;
      bgrp[2] = 0;
      if (write(fd, &bgrp, pitch) == -1)
	return ;
    }
}

void		frame_to_bmp(t_my_framebuffer *framebuffer)
{
  t_rbmp		*header;
  mode_t		mode;
  int			pitch;
  int			fd;

  header = NULL;
  pitch = calcul_pitch(framebuffer->width);
  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  header = header_maker(framebuffer, pitch);
  if ((fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, mode)) == -1)
    return ;
  if (write(fd, header, sizeof(t_rbmp)) == -1)
    return ;
  frame_to_array(framebuffer, fd, pitch);
  close(fd);
}
