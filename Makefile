# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/02 20:38:42 by trobicho          #+#    #+#              #
#    Updated: 2019/11/04 02:16:52 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	g++
CXXFLAGS	=	-std=c++14 -g #-Wall -Wextra
NAME		=	vdb_test

SRCS_PATH	=	./
HDRS_PATH	=	./
OBJS_PATH	=	./obj

INCS_FLAGS	=
LIBS_FLAGS	=

SDL_LOC		=	$(HOME)/.brew/Cellar/sdl2/2.0.9_1
TTF_LOC		=	$(HOME)/.brew/Cellar/sdl2_ttf/2.0.15
SDL_LFLAGS	=	-L $(SDL_LOC)/lib -lSDL2 -L$(TTF_LOC)/lib -lSDL2_ttf
SDL_IFLAGS	=	-I $(HDRS_PATH) -I $(SDL_LOC)/include/SDL2 -I $(SDL_LOC)/include -I $(TTF_LOC)/include -I ./libft

SRCS_NAME	=	main.cpp \
				Renderer.cpp \
				Ray.cpp \
				camera.cpp \
				vector.cpp \
				quaternion.cpp \
				Vdb_test.cpp

HDRS_NAME	=	Vdb_test.h \
				Renderer.h \
				Ray.h \
				camera.h \
				vector.h \
				quaternion.h \
				libvdb.h \
				Root_node.h \
				Internal_node.h \
				Leaf_node.h

OBJS_NAME	=	$(SRCS_NAME:.cpp=.o)

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
HDRS = $(addprefix $(HDRS_PATH)/, $(HDRS_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

all: $(NAME)

$(NAME): $(NAME) $(GEN_OBJS) $(ENV_OBJS) $(OBJS) Makefile
	$(CC) $(CXXFLAGS) $(INCS_FLAGS) $(SDL_IFLAGS) $(SRCS) $(GEN_SRCS) $(ENV_SRCS) $(LIBS_FLAGS) $(SDL_LFLAGS) -o $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp $(HDRS) Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CXXFLAGS) -I $(HDRS_PATH) $(INCS_FLAGS) $(SDL_IFLAGS) -c $< -o $@
	@printf "\e[0K"

clean:
	rm -f $(OBJS) $(GEN_OBJS) $(ENV_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re logo test
