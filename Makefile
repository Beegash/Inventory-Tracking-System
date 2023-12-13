SRCS			= ft_inventoryutils.c ft_loginutils.c ft_main.c
					
OBJS			= $(SRCS:.c=.o)


CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
NAME			= inventorytracking.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)


.PHONY:			all clean fclean re bonus