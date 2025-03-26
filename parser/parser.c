/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/09 18:54:25 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_parser	*new_node(void)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = false;
	node->next = NULL;
	return (node);
}

static void	add_node(t_parser **head, t_parser *node)
{
	t_parser	*tmp;

	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static char	**add_arg(char **args, const char *arg)
{
	int		i;
	char	**new;

	i = 0;
	if (!args)
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(arg);
		new[1] = NULL;
		return (new);
	}
	while (args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args[i])
	{
		new[i] = args[i];
		i++;
	}
	new[i] = ft_strdup(arg);
	i++;
	new[i] = NULL;
	free(args);
	return (new);
}

t_parser	*parser(t_lexer *lexer)
{
	t_parser	*head;
	t_parser	*curr;

	head = NULL;
	curr = NULL;
	while (lexer)
	{
		if (lexer->type_token == T_PIPE)
		{
			curr = NULL;
			lexer = lexer->next;
			continue ;
		}
		if (!curr)
		{
			curr = new_node();
			add_node(&head, curr);
		}
		if (lexer->type_token == T_GENERAL)
			curr->args = add_arg(curr->args, lexer->data);
		else if (lexer->type_token == T_REDIR_IN && lexer->next)
		{
			curr->infile = ft_strdup(lexer->next->data);
			lexer = lexer->next;
		}
		else if ((lexer->type_token == T_REDIR_OUT
				|| lexer->type_token == T_APPEND)
			&& lexer->next)
		{
			curr->outfile = ft_strdup(lexer->next->data);
			curr->append = (lexer->type_token == T_APPEND);
			lexer = lexer->next;
		}
		lexer = lexer->next;
	}
	return (head);
}
