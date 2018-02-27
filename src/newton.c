/*
** newton.c for raytracer2 in /home/benki/Epitech/raytracer2/src/
**
** Made by Lucas Benkemoun
** Login   <lucas.benkemoun@epitech.eu>
**
** Started on  Sat Apr 15 14:48:37 2017 Lucas Benkemoun
** Last update Sun May 28 19:38:24 2017 Melvin Nalepka
*/

double		fcalc(double **av, double x)
{
  double	y;

  y = (av[4]) * pow(x, 4) + (av[3]) * pow(x, 3) + (av[2]) *
    pow(x, 2) + (av[1]) * x + (av[0]);
  return (y);
}

double   	fprime(double **av, double x)
{
  double 	y;

  y = (4 * (av[4]) * pow(x, 3))
    + (3 * (av[3]) * pow(x, 2)) + (2 * (av[2]) * x) + (av[1]);
  return (y);
}

double		newton(double **av)
{
  double        xm;
  double        xmprec;

  xm = 0.5;
  xmprec = 0;
  while (fabs(xm - xmprec) > pow(10, - (av[5])))
    {
      xmprec = xm;
      xm -= (fcalc(av, xm) / fprime(av, xm));
    }
  return (xm);
}
