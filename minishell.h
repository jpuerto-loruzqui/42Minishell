/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:22:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 11:36:49 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h> //para el waitpid
# include "gnl/get_next_line.h"

# define COLOR_BANNER "\033[38;2;0;189;157m"

# define NORMAL_MODE 0
# define DOUBLE_MODE 1
# define SIMPLE_MODE 2

# define COLOR_USERS "\033[38;2;84;222;253m"
# define COLOR_RESET "\033[0m"

typedef enum e_token
{
	T_GENERAL,
	T_NAME_CMD,		// nombre comando
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_INFILE,		// infile
	T_HEREDOC,		// <<
	T_LIMITER,		// limiter del heredoc
	T_REDIR_OUT,	// >
	T_OUTFILE,		// outfile
	T_APPEND,		// >>
}	t_token;

typedef struct s_outfile
{
	char				*data;
	struct s_outfile	*next;
	bool				append;
}	t_outfile;

typedef struct s_strtok
{
	char			*save_ptr;
	char			*token;
	char			*separator;
	int				flag;
}	t_strtok;

typedef struct s_lexer
{
	int				index;		// indice token
	char			*data;		// contenido del token
	int				mode;
	int				type_token;	// tipo de token -> t_token
	struct s_lexer	*next;		// siguiente token
	struct s_lexer	*prev;		// anterior token
}	t_lexer;

typedef struct s_parser
{
	char				**args;		// comando + sus flags
	char				*infile;	// nombre de fichero de entrada (<)
	struct s_outfile	*outfiles;
	struct s_parser		*next;		// siguiente comando
	struct s_outfile	*last_outfile;
	char				*delim;		// delimitador del heredoc
	int					here_fd;
}	t_parser;

typedef struct s_env
{
	char			*content;
	bool			exported;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*commands;
	int			num_commands;
	t_env		*env;
	char		**env_arr;
	bool		error;
	int			last_exit_code;
	int			last_token_type;
	char		*pwd;
	char		*prompt;
	char		*program;
}	t_data;

/****************************************************/
//LEXER
/****************************************************/
t_lexer		*ft_lexer(t_data *data);
void		ft_print_tokens(t_lexer *lexer);
int			ft_is_valid_char(char command);
int			ft_is_valid_slash(char command);
t_lexer		*ft_new_tok(int index, char *data, t_token type, int *mode);
void		ft_add_tok(t_lexer **lexer, t_lexer *new);
int			ft_check_mode(char c, int mode);
char		ft_check_quote(char *c);
void		ft_init_strtok_struct(t_strtok *s, char *str);
char		*ft_check_separator(char *sep);
t_lexer		*ft_get_last_node(t_lexer *head);

/****************************************************/
//PARSER
/****************************************************/
t_parser	*ft_parser(t_lexer *lexer, t_data data);
char		*ft_expand_cmd(char *token, char **env_arr);
t_parser	*ft_new_node(void);
void		ft_add_node(t_parser **head, t_parser *node);
int			ft_parser_expand(t_lexer **lexer, t_data data);
int			ft_parse_redirs(t_lexer **lexer, t_parser **curr,
				t_outfile **last_out, t_data data);
int			ft_parse_heredoc(t_lexer **lexer, t_parser **curr);
void		ft_check_parser_curr(t_parser **curr, t_outfile **last_out,
				t_parser **head);
int			ft_parse_pipes(t_lexer **lexer, t_parser **curr);
t_outfile	*ft_new_outfile(t_lexer *lexer, t_data data);
t_outfile	*ft_append_outfile(t_outfile **head, t_outfile *new);

/****************************************************/
//UTILS
/****************************************************/
char		*ft_strtok(char *str, int *mode, t_data *data);
void		ft_manage_slash(char **str, char delim);
int			ft_check_format(char **save_ptr, char delim, int *i, t_data *data);
char		*ft_append_char(char *str, char c);
int			ft_parserlen(t_parser *parser);
void		ft_free_split(char **split);
char		**ft_lsttoa(t_data data);
t_env		*ft_dup_env(char **envp);
t_env		*ft_new_node_env(void *content);
void		ft_envadd_back(t_env **lst, t_env *new);
char		*ft_getenv(const char *cmd, char **env_arr);
bool		ft_is_not_escaped(char *ptr, int i);
char		*ft_control_getcwd(t_data *data);
bool		ft_error_tokens(t_data *data);
void		ft_update_shlvl(char ***env);
char		*ft_get_prompt(t_data *data);
void		ft_export_env(char ***env, char *var, char *new_entry);

/****************************************************/
//BUILT-INS
/****************************************************/
bool		ft_is_built_in(t_parser *commands, t_data *data);
void		ft_unset_std(int *std_inout);
void		ft_exit(t_parser *parser, t_data *data);
void		ft_exit_error(char *message, t_data *data, int code);
int			ft_cd(char **args, t_data *data);
int			ft_pwd(char **args);
int			ft_echo(char **arg);
int			ft_env(char **args, t_env *envp);
t_env		*ft_unset(char **args, t_env *envp);
int			ft_export(char **args, t_data *data);
void		ft_create_var(t_env **new_var, char *args, t_data *data);
int			ft_check_var(char *arg, t_data *data);
int			*ft_redir_builtin(t_parser *commands);

/****************************************************/
//EXEC BUILT-INS
/****************************************************/
bool		ft_exec_jp(t_parser *cmd, int *stdinout, t_data *data);
bool		ft_exec_exit(t_parser *cmd, int *stdinout, t_data *data);
bool		ft_exec_cd(t_parser *cmd, t_data *data, int *stdinout);
bool		ft_exec_pwd(t_parser *cmd, int *stdinout, t_data *data);
bool		ft_exec_echo(t_parser *cmd, int *stdinout);
bool		ft_exec_env(t_parser *cmd, t_data *data, int *stdinout);
bool		ft_exec_unset(t_parser *cmd, t_data *data, int *stdinout);
bool		ft_exec_export(t_parser *cmd, t_data *data, int *stdinout);
bool		ft_exec_shell(t_parser *cmd, t_data *data, int *stdinout);

/****************************************************/
//SIGNALS
/****************************************************/
void		ft_sigint_handler(int sig);
void		ft_sigint_visualizer(int sig);

/****************************************************/
//EXEC
/****************************************************/
void		ft_exec_one_command(t_data *data);
void		ft_exec_pipes(t_data *data);
void		ft_init_pipes(int num_commands, int ***array_pipes,
				pid_t **array_pids);
void		ft_finish_exec(int num_commands, int ***array_pipes,
				pid_t **array_pids);
void		ft_close_unused_pipes(int num_commands, int i, int ***array_pipes);
void		ft_close_all_pipes(t_data *data, int **array_pipes);
void		ft_find_path(t_parser *commands, char **envp);
void		ft_exec_child(int i, int ***array_pipes, t_parser *cmd,
				t_data *data);
void		ft_manage_infile(t_parser *commands);

/****************************************************/
//REDIRECTIONS
/****************************************************/
void		ft_input_redir(t_parser *commands);
void		ft_output_redir(t_parser *commands);
void		ft_check_redirs(t_parser *cmd, t_data *data);

/****************************************************/
//FREES
/****************************************************/
void		ft_free_lexer(t_lexer *lexer);
void		ft_free_parser(t_parser *parser);
void		ft_free_data(t_data data);
void		ft_free_env(t_data *data);

/****************************************************/
//HEREDOC
/****************************************************/
int			ft_heredoc(char *delim, t_parser *commands);

/****************************************************/
//TEXT VISUALIZER
/****************************************************/
void		ft_show_visualizer(char *file);
void		ft_set_raw_mode(int fd);
void		ft_restore_terminal(int fd);
char		ft_read_key(void);

#endif
