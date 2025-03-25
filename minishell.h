/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:22:55 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/09 18:51:20 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define COLOR_BANNER "\033[38;2;0;189;157m"
# define COLOR_RESET  "\033[0m"

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
	int				type_token;	// tipo de token -> t_token
	struct s_lexer	*next;		// siguiente token
}	t_lexer;

/**
 * @brief Nodo en la lista de análisis sintáctico.
 */
typedef struct s_parser
{
	char			**args;		// comando + sus argumentos
	char			*infile;	// nombre de fichero de entrada (<)
	char			*outfile;	// nombre de fichero de salida (>, >>)
	int				append;		// 0 si “>”, 1 si “>>”
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
char		*ft_strtok(char *str, const char *delim);

/****************************************************/
//BUILT-INS
/****************************************************/
void	ft_exit(void);

#endif
