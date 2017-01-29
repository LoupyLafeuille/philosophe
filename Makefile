##
## Makefile for malloc in /home/gaonac_l/rendu/PSU_2015_malloc
##
## Made by
## Login   <gaonac_l@epitech.net>
##
## Started on  Mon Jan 25 19:52:46 2016
## Last update Thu Feb 11 20:56:51 2016 
##

NAME	=	libmy_malloc.so

CC	=	gcc

CFLAGS	+=	-fPIC -W -Wall -Werror -Wextra -I./include

LDFLAGS	+=	-shared -lm -lpthread

RM	=	rm -f

SRCS	=	src/malloc.c		\
		src/link_list.c		\
		src/tools.c		\
		src/free.c		\
		src/realloc.c		\
		src/calloc.c		\
		src/thread.c		\
		src/show_alloc_mem.c	\

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS) $(TESTOBJ)

fclean	:	clean
		$(RM) $(NAME) $(TEST)

re	:	fclean all

.PHONY	:	fclean re all
