CC = cc
CFLAGS = -Wall -Wextra -Werror

srcs = color.c main.c ray.c vec3.c object/sphere.c

srcs := $(addprefix src/, $(srcs))
OBJS := $(srcs:.c=.o)
NAME = minirt
# LIBFT = NONE

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
	@echo "$(CLEAR_LINE)	[ $(SKYBLUE)$(NAME) $(RESET)] $(GREEN)created$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I includes
	@echo "\n How to run $(SKYBLUE)$(NAME)"
	@echo "\n	$(SKYBLUE)./$(NAME)$(RESET)"

# 추후 libft 추가 후 사용
# $(LIBFT):
# 	@make -C libft
# 	@mkdir -p libs
# 	@cp libft/libft.a libs/


%.o : %.c
	@printf "$(CLEAR_LINE)			$(BLUE)~~ $(RESET)Making object for $(SKYBLUE)(miniRT) $(BLUE)~~$(RESET)\n"
	@printf "$(CLEAR_LINE)		$(BLUE)~~$(RESET) $(RESET) Making $(YELLOW)$@$(RESET) from $(YELLOW)$<$(RESET) $(BLUE)~~$(RESET)$(MOVE_UP)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes

clean:
	@sleep 0.5
	@echo "$(CLEAR_LINE)		$(YELLOW)~~$(RED)Cleaing Object files $(YELLOW)~~$(RESET)\n$(MOVE_DOWN)"
	@rm -rf $(OBJS)
	@sleep 0.1
	@echo "$(CLEAR_LINE)		$(RED)Removing Object files.$(RESET)"
	@sleep 0.2
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing Object files..$(RESET)"
	@sleep 0.1
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing Object files...$(RESET)"
	@sleep 0.1
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(YELLOW)Object files$(RESET) $(RED)removed$(RESET)$(MOVE_DOWN)"

fclean: clean
	@rm -f $(NAME) $(TEST_EXEC) $(prs_TEST_EXEC) $(EXECUTE_TEST_EXEC)
	@sleep 0.5
	@echo "$(CLEAR_LINE)		[ $(SKYBLUE)$(NAME) $(RESET)] $(RED)removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
