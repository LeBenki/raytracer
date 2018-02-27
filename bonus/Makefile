##
## Makefile for Makefile in /home/benki/Epitech/raytracer2
##
## Made by Lucas Benkemoun
## Login   <lucas.benkemoun@epitech.eu>
##
## Started on  Mon May  1 17:08:45 2017 Lucas Benkemoun
## Last update Thu Jun  1 11:00:40 2017 
##

CC	=	@mpicc

RM	=	rm -f

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[1;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[1;31m"

CFLAGS  +=	-Wextra -Wall -Werror
CFLAGS	+=	-Iinclude -lm
CFLAGS	+=	-lc_graph_prog -pthread

NAME	=	raytracer2

SRCS	=	main.c 				\
		../utils/window.c 		\
		../utils/my_put_pixel.c 	\
		../src/calc_dir_vector.c 	\
		../utils/util_graph.c 		\
		../utils/util_calc.c 		\
		../src/sphere.c 		\
		../src/cylinder.c 		\
		../src/cone.c 			\
		../src/plane.c 			\
		../src/rotate.c 		\
		../src/translate.c 		\
		../src/paraboloide.c 		\
		../src/hyperboloide.c 		\
		../src/calcul.c 		\
		../src/init.c 			\
		../src/read_xml.c 		\
		../utils/display.c 		\
		../utils/my_strncpy.c 		\
		../utils/my_str_to_wordtab.c 	\
		../utils/my_getnbr.c 		\
		../src/calcul_shadow.c 		\
		../src/my_rotate.c 		\
		../src/transparence.c		\
		../src/reflection.c		\
		../src/light.c			\
		../src/raytracer.c		\
		../src/reader_bmp.c		\
		../src/filters.c		\
		../src/color_op.c		\
		../src/frame_to_bmp.c		\
		../src/menu.c			\
		../src/anti_aliasing.c		\
		../src/init_calcul.c		\
		../src/calcul_form.c		\
		../src/texture.c		\
		../src/threads.c		\
		../src/damier.c			\
		../src/perlimpinpin.c		\
		src/cluster.c			\
		src/color_pixel.c		\
		src/init.c			\
		../src/menu2.c

OBJS	=	$(SRCS:.c=.o)

all		:	title $(NAME)
			@echo ""

title		:
			@$(ECHO) $(GREEN)"\nProjet : Raytracer2\n" $(DEFAULT)

$(NAME)		:	$(OBJS)
			@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) &&				\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $(NAME) $(DEFAULT) ||	\
			$(ECHO) $(RED) "[KO]" $(TEAL) $(NAME) $(DEFAULT)

.c.o		:
			@$(CC) $(CFLAGS) -c $< -o $@ &&				\
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) ||	\
			$(ECHO) $(RED) "[KO]" $(TEAL) $< $(DEFAULT)

clean		:
			@$(RM) $(OBJS)

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
