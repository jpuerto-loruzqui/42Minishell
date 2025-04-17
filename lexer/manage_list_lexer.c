/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:29:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 14:02:55 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_new_tok(int index, char *data, t_token type, int *mode)
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
	token->prev = NULL;
	return (token);
}

void	ft_add_tok(t_lexer **lexer, t_lexer *new)
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
		new->prev = tmp;
	}
}

t_lexer	*ft_get_last_node(t_lexer *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
