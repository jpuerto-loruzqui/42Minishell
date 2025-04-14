NAME = minishell
SRC = main.c lexer/lexer.c parser/parser.c utils/ft_strtok.c built-ins/ft_exit.c\
	signals.c built-ins/ft_cd.c built-ins/ft_pwd.c built-ins/is_built_in.c\
	exec/exec_one_command.c exec/exec.c utils/ft_parserlen.c\
	exec/exec_pipes.c exec/pipes_childs.c redirections/input_redir.c redirections/output_redir.c\
	free_structs.c built-ins/ft_exit_error.c utils/ft_append_char.c parser/expand_cmd.c\
	built-ins/ft_echo.c built-ins/ft_env.c built-ins/ft_unset.c\
	heredoc/heredoc.c gnl/get_next_line.c gnl/get_next_line_utils.c built-ins/ft_export_utils.c\
	utils/ft_dup_env.c utils/ft_lsttoa.c built-ins/ft_export.c utils/ft_getenv.c\
	lexer/manage_list_lexer.c parser/manage_list_parser.c text_visualizer/ft_jp.c\
	text_visualizer/ft_jp_utils.c built-ins/exec_built_ins_1.c built-ins/exec_built_ins_2.c\
	exec/close_pipes.c\

SRC_PRINT = print/main_print.c lexer/lexer.c parser/parser.c utils/ft_strtok.c built-ins/ft_exit.c\
	signals.c built-ins/ft_cd.c built-ins/ft_pwd.c built-ins/is_built_in.c\
	exec/exec_one_command.c exec/exec.c utils/ft_parserlen.c\
	exec/exec_pipes.c exec/pipes_childs.c redirections/input_redir.c redirections/output_redir.c\
	free_structs.c built-ins/ft_exit_error.c utils/ft_append_char.c parser/expand_cmd.c\
	built-ins/ft_echo.c built-ins/ft_env.c built-ins/ft_unset.c\
	heredoc/heredoc.c gnl/get_next_line.c gnl/get_next_line_utils.c built-ins/ft_export_utils.c\
	utils/ft_dup_env.c utils/ft_lsttoa.c built-ins/ft_export.c utils/ft_getenv.c print/print.c\
	lexer/manage_list_lexer.c parser/manage_list_parser.c text_visualizer/ft_jp.c\
	text_visualizer/ft_jp_utils.c built-ins/exec_built_ins_1.c built-ins/exec_built_ins_2.c\
	exec/close_pipes.c\

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_PRINT = $(SRC_PRINT:%.c=$(OBJ_DIR)/%.o)
NAME_PRINT = minishell_print

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
	@rm -rf $(OBJ_PRINT)
	@rm -f $(NAME)
	@rm -f $(NAME_PRINT)
	@printf "$(COLOR_CLEAN)Full clean complete!$(RESET)\n"

print: $(OBJ_PRINT)
	@$(MAKE) --no-print-directory -C libft
	@$(CC) $(CFLAGS) $(OBJ_PRINT) $(LDFLAGS) -o $(NAME_PRINT)
	./minishell_print

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re print
