### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -pthread #-g3 -fsanitize=thread #-fsanitize=address

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCS_PATH			= include/
SRCS_PATH			= src/

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME			= philo

SRC_FILES		= main.c \
				  philos.c \
				  actions.c \
				  parse.c \
				  time.c \
				  safe_mutex.c \
				  safe_mutex2.c

UTILS_FILES		= utils/ft_atoi.c \
				  utils/ft_isdigit.c \
				  utils/ft_strlen.c \
				  utils/ft_strdigit.c

ALL_FILES = $(SRC_FILES) $(UTILS_FILES)

MAND_OBJS = $(ALL_FILES:%.c=bin/%.o)

### ---   ---   ---         ---   ---   --- ###
#              COLORS & EXTRAS :)             #
### ---   ---   ---         ---   ---   --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033[1;37m'
BLUE	= '\033[1;34m'

### ---   ---   ---         ---   ---   --- ###
#                  GAME RULES                 #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(MAND_OBJS)
	@echo $(PURPLE)"[Creating $(NAME) "$(PURPLE)"]"$(WHITE)
	$(CC) $(CFLAGS) $(MAND_OBJS) -I $(INCS_PATH) -o $(NAME)

bin/%.o: src/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)
	@rm -rf bin

fclean: clean 
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)
	@rm -f $(NAME)

re: fclean all

