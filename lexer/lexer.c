/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/25 17:09:52 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Crea un nuevo nodo de la lista del léxico.
 */
static t_lexer	*new_token(int index, char *data, t_token type)
{
	t_lexer	*token;

	token = malloc(sizeof(t_lexer));
	if (!token)
		return (NULL);
	token->index = index;
	token->data = ft_strdup(data);
	token->type_token = type;
	token->next = NULL;
	return (token);
}

/**
 * @brief Añade un nodo a la lista de tokens.
 */
static void	add_token(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*tmp;

	if (!*lexer)
		*lexer = new;
	else
	{
		tmp = *lexer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/**
 * @brief Divide la entrada en tokens.
 */
t_lexer	*lexer(char *input)
{
	t_lexer	*lexer_list;
	char	*token;
	int		index;
	t_token	type;

	lexer_list = NULL;
	index = 0;
	token = ft_strtok(input, " \t\n");
	while (token)
	{
		type = T_GENERAL;
		if (ft_strncmp(token, "|", 1) == 0)
			type = T_PIPE;
		else if (ft_strncmp(token, "<<", 2) == 0)
			type = T_HEREDOC;
		else if (ft_strncmp(token, ">>", 2) == 0)
			type = T_APPEND;
		else if (ft_strncmp(token, "<", 1) == 0)
			type = T_REDIR_IN;
		else if (ft_strncmp(token, ">", 1) == 0)
			type = T_REDIR_OUT;
		add_token(&lexer_list, new_token(index++, token, type));
		token = ft_strtok(NULL, " \t\n");
	}
	return (lexer_list);
}

/**
 * @brief Imprime la lista de tokens.
 */
void	print_tokens(t_lexer *lexer)
{
	while (lexer)
	{
		printf("Token %d: [%s] -> Tipo %d\n", lexer->index, \
			lexer->data, lexer->type_token);
		lexer = lexer->next;
	}
}
