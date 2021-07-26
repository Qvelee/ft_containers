# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 16:22:01 by nelisabe          #+#    #+#              #
#    Updated: 2021/07/26 14:45:09 by nelisabe         ###   ########.fr        #
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

NAME =			webserv

COMP ?=			clang++

FLAGS ?=		-g -std=c++98 -Wall -Wextra -Werror

INCLUDES ?=		-I.

#SRC DIRS

SRC_DIR =		./

#SRC

SRC =			main.cpp \
				vector.cpp

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
	@$(COMP) $(FLAGS) $< $(INCLUDES) -o $@ -MMD
	@echo -e "$(YELLOW)$(BOLD)$(NAME) created!$(RESET)"

$(addprefix $(OBJ_DIR), %.o): %.cpp
	@$(COMP) -c $(FLAGS) $(INCLUDES) $< -o $@ -MMD

clean:
	@echo -e "$(GRAY)Deleting...$(RESET)"
	@rm -rf temp

fclean: clean
	@rm -rf $(NAME)
	@echo -e "$(RED)$(BOLD)$(NAME) deleted!$(RESET)"

re: fclean all

include $(wildcard $(D_FILES))

.PHONY: all, re, clean, fclean
