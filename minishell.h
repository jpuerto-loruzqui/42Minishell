/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:22:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 13:42:46 by jpuerto- &       ###   ########.fr       */
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

# define VALID_CHARS "+*?=_/-.0123456789abcdefghijklmn\
	ñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ<>\\ \"\'|$"

# define COLOR_USERS "\033[38;2;84;222;253m"
# define COLOR_RESET "\033[0m"

/**
 * @brief Tipos de tokens
 */
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

/**
 * @brief Nodo en la lista de análisis léxico.
 */

typedef struct s_outfile
{
	char				*data;
	struct s_outfile	*next;
	bool				append;
}	t_outfile;

typedef struct s_lexer
{
	int				index;		// indice token
	char			*data;		// contenido del token
	int				mode;
	int				type_token;	// tipo de token -> t_token
	struct s_lexer	*next;
	struct s_lexer	*prev;		// siguiente token
}	t_lexer;

/**
 * @brief Nodo en la lista de análisis sintáctico.
 */
typedef struct s_parser
{
	char				**args;		// comando + sus flags
	char				*infile;	// nombre de fichero de entrada (<)
	struct s_outfile	*outfiles;
	struct s_parser		*next;		// siguiente comando (pipe)
	struct s_outfile	*last_outfile;
	char				*delim;
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
	char		*term_log;
}	t_data;

/****************************************************/
//LEXER
/****************************************************/
t_lexer		*lexer(t_data *data);
void		print_tokens(t_lexer *lexer);

/****************************************************/
//PARSER
/****************************************************/
t_parser	*parser(t_lexer *lexer, t_data data);
char		*expand_cmd(char *token, char **env_arr);
t_parser	*new_node(void);

/****************************************************/
//UTILS
/****************************************************/
char		*ft_strtok(char *str, int *mode, t_data *data);
char		*append_char(char *str, char c);
int			ft_parserlen(t_parser *parser);
void		ft_free_split(char **split);
char		**ft_lsttoa(t_data data);
t_env		*ft_dup_env(char **envp);
t_env		*new_node_env(void *content);
void		ft_envadd_back(t_env **lst, t_env *new);
char		*ft_getenv(const char *cmd, char **env_arr);

/****************************************************/
//BUILT-INS
/****************************************************/

bool		is_built_in(t_parser *commands, t_data *data);
void		ft_exit(t_parser *parser);
void		exit_error(char *message);
void		unrecognized_error(char *command);
int			ft_cd(char **args, t_data *data);
int			ft_pwd(char **args);
int			ft_echo(char **arg);
int			ft_env(char **args, t_env *envp);
t_env		*ft_unset(char **args, t_env *envp);
int			ft_export(char **args, t_data *data);
void		create_var(t_env **new_var, char *args, t_data *data);
int			check_var(char *arg, t_data *data);

/****************************************************/
//SIGNALS
/****************************************************/
void		sigint_handler(int sig);
void		sigint_visualizer(int sig);

/****************************************************/
//EXEC
/****************************************************/
char		*ft_get_path_from_env(char **envp);
char		*ft_find_executable(char *command, char **envp);
void		exec_one_command(t_data *data);
void		exec_pipes(t_data *data);
void		init_pipes(int num_commands, int ***array_pipes,
				pid_t **array_pids);
void		finish_exec(int num_commands, int ***array_pipes,
				pid_t **array_pids);
void		close_unused_pipes(int num_commands, int i, int ***array_pipes);
void		find_path(t_parser *commands, char **envp);
void		exec_child(int i, int ***array_pipes, t_parser *cmd, t_data *data);

/****************************************************/
//REDIRECTIONS
/****************************************************/
void		input_redir(t_parser *commands);
void		output_redir(t_parser *commands);
void		input_redir_last(t_parser *commands);
void		check_redirs(t_parser *cmd, t_data *data);

/****************************************************/
//FREES
/****************************************************/
void		free_lexer(t_lexer *lexer);
void		free_parser(t_parser *parser);
void		free_data(t_data data);
void		free_env(t_data *data);

/****************************************************/
//HEREDOC
/****************************************************/
char		*get_heredoc_delimiter(t_lexer *tokens);
int			ft_heredoc(char *delim, t_parser *commands);

#endif
