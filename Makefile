# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 16:22:01 by nelisabe          #+#    #+#              #
#    Updated: 2021/08/12 12:24:58 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS =		--no-print-directory

### colors ###
RESET =			\033[0m
BOLD =			\033[1m
RED =			\033[31m
GREEN =			\033[32m
YELLOW =		\033[33m
GRAY =			\033[2m
##############

NAME =			containers

COMP ?=			clang++

FLAGS ?=		-g -std=c++98 -Wall -Wextra -Werror

MODE ?=			0

INCLUDES ?=		-I. -I./iterators/ -I./vector/ -I./stack/

#SRC DIRS

SRC_DIR =		./

#SRC

SRC =			main.cpp

#OBJ DIRS

OBJ_DIR =		./temp/

#OBJ

OBJ =			$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

D_FILES = 		$(patsubst %.o, %.d, $(OBJ))

###

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(COMP) $(FLAGS) -D MODE=$(MODE) $< $(INCLUDES) -o $@ -MMD
	@echo -e "$(GREEN)$(BOLD)$(NAME) created!$(RESET)"

$(addprefix $(OBJ_DIR), %.o): %.cpp
	@$(COMP) -c $(FLAGS) -D MODE=$(MODE) $(INCLUDES) $< -o $@ -MMD

clean:
	@echo -e "$(GRAY)Deleting...$(RESET)"
	@rm -rf temp

fclean: clean
	@rm -rf $(NAME)
	@echo -e "$(RED)$(BOLD)$(NAME) deleted!$(RESET)"

re: fclean all

include $(wildcard $(D_FILES))

.PHONY: all, re, clean, fclean
