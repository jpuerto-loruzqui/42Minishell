NAME = minishell

SRC = main.c lexer/lexer.c parser/parser.c utils/ft_strtok.c built-ins/ft_exit.c\
	signals.c built-ins/ft_cd.c built-ins/ft_pwd.c built-ins/is_built_in.c\
	exec/exec_one_command.c exec/exec.c utils/ft_parserlen.c utils/ft_free_split.c\
	exec/exec_pipes.c exec/pipes_childs.c redirections/input_redir.c redirections/output_redir.c\
	free_structs.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L/usr/local/opt/readline -lreadline -L ./libft -lft
INCLUDES = -I/usr/local/opt/readlineinclude

COLOR_BANNER = \033[38;2;0;189;157m
COLOR_COMPILATION = \033[38;2;73;198;229m
COLOR_CLEAN = \033[38;2;139;215;210m
COLOR_USERS = \033[38;2;84;222;253m
RESET = \033[0m

$(NAME): $(OBJ)
	@$(MAKE) --no-print-directory -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@printf "$(COLOR_BANNER)"
	@echo " _  _  __  __ _  __  ____  _  _  ____  __    __   "
	@echo "( \/ )(  )(  ( \(  )/ ___)/ )( \(  __)(  )  (  )  "
	@echo "/ \/ \ )( /    / )( \___ \) __ ( ) _) / (_/\/ (_/\\"
	@echo "\_)(_/(__)\_)__)(__)(____/\_)(_/(____)\____/\____/"
	@printf "$(COLOR_USERS)By jpuerto- & loruzqui\n"
	@echo ""
	@printf "$(COLOR_COMPILATION)Compilation complete!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean --no-print-directory -C libft
	@rm -rf $(OBJ_DIR)
	@printf "$(COLOR_CLEAN)Clean complete!$(RESET)\n"

fclean:
	@$(MAKE) fclean --no-print-directory -C libft
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@printf "$(COLOR_CLEAN)Full clean complete!$(RESET)\n"

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
