NAME		=		philosopher

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

SRC			=		main.c \
					philo.c

OBJS		=		$(SRC:%.c=$(BUILD_DIR)%.o)

DEPS		=		$(OBJS).d

CFLAGS		=		-Wall -Werror -Wextra

IFLAGS		=		-I$(INC_DIR)

DFLAGS		=		-MMD -MP

RM			=		rm -rf

MKDIR		=		mkdir -p

all:				$(NAME)

$(NAME):			$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
				$(MKDIR) $(shell dirname $@)
				$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $< -o $@