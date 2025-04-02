/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:22:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/01 15:48:41 by jpuerto-         ###   ########.fr       */
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

# define COLOR_BANNER "\033[38;2;0;189;157m"

# define NORMAL_MODE 0
# define DOUBLE_MODE 1
# define SIMPLE_MODE 2

# define VALID_CHARS "0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ<> \"\'|$"

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
typedef struct s_lexer
{
	int				index;		// indice token
	char			*data;		// contenido del token
	int				mode;
	int				type_token;	// tipo de token -> t_token
	struct s_lexer	*next;		// siguiente token
}	t_lexer;

/**
 * @brief Nodo en la lista de análisis sintáctico.
 */
typedef struct s_parser
{
	char			**args;		// comando + sus flags
	char			*infile;	// nombre de fichero de entrada (<)
	char			*outfile;	// nombre de fichero de salida (>, >>)
	bool			append;		// false si “>”, true si “>>”
	struct s_parser	*next;		// siguiente comando (pipe)
}	t_parser;

/****************************************************/
//LEXER
/****************************************************/
t_lexer		*lexer(char *input);
void		print_tokens(t_lexer *lexer);

/****************************************************/
//PARSER
/****************************************************/
t_parser	*parser(t_lexer *lexer);

/****************************************************/
//UTILS
/****************************************************/
char		*ft_strtok(char *str, int *mode);
char	*append_char(char const *s1, char c);
int			ft_parserlen(t_parser *parser);
void		ft_free_split(char **split);

/****************************************************/
//BUILT-INS
/****************************************************/

bool		is_built_in(t_parser *commands);
void		ft_exit(t_parser *parser);
void	  	exit_error(char *message);
void 		unrecognized_error(char *command);
int			ft_cd(char **args);
int			ft_pwd(char **args);

/****************************************************/
//SIGNALS
/****************************************************/
void		sigint_handler(int sig);

/****************************************************/
//EXEC
/****************************************************/
char		*ft_get_path_from_env(char **envp);
char		*ft_find_executable(char *command, char **envp);
void		exec_one_command(t_parser *commands, char **envp);
void		exec_pipes(t_parser *commands, char **envp, int num_commands);
void		init_pipes(int num_commands, int ***array_pipes, pid_t **array_pids);
void		finish_exec(int num_commands, int ***array_pipes, pid_t **array_pids);
void		close_unused_pipes(int num_commands, int i, int ***array_pipes);
void		find_path(t_parser *commands, char **envp);
void		exec_child(int i, int num_commands, int ***array_pipes,
				t_parser *commands, char **envp);

/****************************************************/
//REDIRECTIONS
/****************************************************/
void		input_redir(t_parser *commands);
void		output_redir(t_parser *commands);

/****************************************************/
//FREES
/****************************************************/
void		free_lexer(t_lexer *lexer);
void		free_parser(t_parser *parser);


#endif
