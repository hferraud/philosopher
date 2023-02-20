NAME		=		philosopher

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

SRC			=		main.c \
					philo.c \
					philo_init.c \
					parser.c \
					fork.c \

OBJS		=		$(SRC:%.c=$(BUILD_DIR)%.o)

DEPS		=		$(OBJS:.o=.d)

CFLAGS		=		-Wall -Werror -Wextra

IFLAGS		=		-I$(INC_DIR)

DFLAGS		=		-MMD -MP

RM			=		rm -rf

MKDIR		=		mkdir -p

all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(OBJS)
				$(CC) $(OBJS) -o $@

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
				$(MKDIR) $(shell dirname $@)
				$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

clean:
				$(RM) $(BUILD_DIR)

fclean:				clean
				$(RM) $(NAME)

re:					fclean
				$(MAKE) all

.PHONY:				all clean fclean re
