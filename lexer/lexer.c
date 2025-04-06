/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/01 12:26:20 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Crea un nuevo nodo de la lista del léxico.
 */
static t_lexer	*new_token(int index, char *data, t_token type, int *mode)
{
	t_lexer	*token;

	token = malloc(sizeof(t_lexer));
	if (!token)
		return (NULL);
	token->index = index;
	token->data = ft_strdup(data);
	token->mode = *mode;
	token->type_token = type;
	token->next = NULL;
	(*mode) = NORMAL_MODE;
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
t_lexer	*lexer(t_data *data)
{
	t_lexer	*lexer_list;
	char	*token;
	int		index;
	int		mode;
	t_token	type;

	mode = NORMAL_MODE;
	lexer_list = NULL;
	index = 0;
	token = ft_strtok(data->input, &mode, data);
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
		if (token[0])
			add_token(&lexer_list, new_token(index++, token, type, &mode));
		if (token[0])
			free(token);
		token = ft_strtok(NULL, &mode, data);
		if (data->error)
			return (NULL);
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
		printf("Token %d: [%s] -> Tipo %d\n", lexer->index,
			lexer->data, lexer->type_token);
		lexer = lexer->next;
	}
}
