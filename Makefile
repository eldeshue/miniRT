
# compiler option
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm -L. -lmlx -L./src/libft -lft -L./src/ft_graphics -lftgraphics -L./src/ft_graphics/ft_math -lftmath -L./src/ft_string -lftstring -L./src/ft_vector -lftvector

# target rule
NAME = miniRT

srcs = ./src/raytracer/reflect.c \
./src/colliders/colliders_utils.c \
./src/colliders/colliders_utils2.c \
./src/colliders/colliders_plane.c \
./src/colliders/colliders_sphere.c \
./src/colliders/colliders_cylinder.c \
./src/colliders/colliders_cylinder_caps.c \
./src/colliders/colliders_cylinder_surface.c \
./src/colliders/colliders_cone.c \
./src/light/light.c \
./src/main.c \
./src/raytracer/render_image.c \
./src/raytracer/render_resource.c \
./src/raytracer/render_window.c \
./src/raytracer/set_rt_hook.c \
./src/raytracer/trace_ray.c \
./src/raytracer/utility.c \
./src/raytracer/view_plane.c \
./src/rt_object/rt_geo.c \
./src/rt_object/rt_obj.c \
./src/parser/prs_error_exit.c \
./src/parser/prs_readfile.c \
./src/parser/prs_atof.c \
./src/parser/prs_object.c \
./src/parser/prs_scene.c

OBJS := $(srcs:.c=.o)

# path
FT_GRAPHICS_DIR = ./src/ft_graphics
FT_STRING_DIR = ./src/ft_string
FT_VECTOR_DIR = ./src/ft_vector
LIBFT_DIR = ./src/libft

# 색상 정의
SKYBLUE=\033[0;36m
BLUE=\033[0;34m
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
RESET=\033[0m
CLEAR_LINE=\033[2K\r
MOVE_UP=\033[1A
MOVE_DOWN=\033[1B


# arm architecture compatibility
# 추후 rt의 MiniLibX를 위한 커스텀 플래그
# ifeq ($(shell uname -p), arm)
# 	READLINE_PATH = -I /opt/homebrew/opt/readline/include
# 	READLINE_FLAGS += $(READLINE_PATH) -L/opt/homebrew/opt/readline/lib
# endif

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(FT_GRAPHICS_DIR)
	$(MAKE) -C $(FT_STRING_DIR)
	$(MAKE) -C $(FT_VECTOR_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	if ! [ -f "./libmlx.dylib" ]; then \
		mv ./src/libmlx.dylib ./; \
	fi
	@$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:

	$(MAKE) -C $(FT_GRAPHICS_DIR) clean
	$(MAKE) -C $(FT_STRING_DIR) clean
	$(MAKE) -C $(FT_VECTOR_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)


fclean: clean
	if [ -f "./libmlx.dylib" ]; then \
		mv ./libmlx.dylib ./src; \
	fi
	$(MAKE) -C $(FT_GRAPHICS_DIR) fclean
	$(MAKE) -C $(FT_STRING_DIR) fclean
	$(MAKE) -C $(FT_VECTOR_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
