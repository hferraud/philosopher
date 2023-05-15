NAME		=		philo

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

SRC			=		main.c \
					philo.c \
					philo_eat.c \
					philo_init.c \
					philo_clear.c \
					philo_time.c \
					philo_utils.c \
					philo_print.c \
					philo_equalizer.c \
					parser.c \
					fork.c \

OBJS		=		$(SRC:%.c=$(BUILD_DIR)%.o)

DEPS		=		$(OBJS:.o=.d)

CFLAGS		=		-Wall -Werror -Wextra -pthread -fsanitize=address

IFLAGS		=		-I$(INC_DIR)

DFLAGS		=		-MMD -MP

RM			=		rm -rf

MKDIR		=		mkdir -p

# RULES

all:				$(NAME)

-include			$(DEPS)

$(NAME):			$(OBJS)
				$(CC) $(OBJS) $(CFLAGS) -o $@

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
