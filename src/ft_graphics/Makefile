# result file name
NAME = libftgraphics.a

# compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# sub library
MLX_LIB = ./mlx/libmlx.a
MLX_DIR = ./mlx
FT_MATH_LIB = ./ft_math/libftmath.a
FT_MATH_DIR = ./ft_math

AR = ar
ARFLAGS = -src

SRCS = ft_mlx_object.c ft_render_line.c ft_render_pixel.c ft_interpolate_color.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C $(FT_MATH_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(MAKE) -C $(FT_MATH_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(FT_MATH_DIR) fclean
	rm -f $(MLX_LIB)
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: clean fclean re all
