### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCS_PATH			= include/
SRCS_PATH			= src/

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME			= philo

SRC_FILES		= main.c

MAND_OBJS = $(SRC_FILES:%.c=bin/%.o)

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
	@mkdir -p bin
	$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)
	@rm -rf bin
	@echo $(RED)"[Deleting Libft Object Files]"$(WHITE)

fclean: clean 
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)
	@rm -f $(NAME)

re: fclean all

