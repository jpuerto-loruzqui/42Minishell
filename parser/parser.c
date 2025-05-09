/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/09 11:42:54 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_add_arg(char **args, const char *arg)
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

t_outfile	*ft_append_outfile(t_outfile **head, t_outfile *new)
{
	t_outfile	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_outfile	*ft_new_outfile(t_lexer *lexer, t_data data)
{
	t_outfile	*node;

	node = malloc(sizeof(t_outfile));
	if (!node)
		return (NULL);
	node->append = (lexer->type_token == T_APPEND);
	if (lexer->next->data)
	{
		if (lexer->next->mode != SIMPLE_MODE)
			ft_parser_expand(&lexer->next, data);
		node->data = ft_strdup(lexer->next->data);
	}
	else
		node->data = NULL;
	node->next = NULL;
	return (node);
}

static void	ft_parse_general_token(t_lexer *lexer, t_parser *curr)
{
	int		i;
	char	**split;

	if (lexer->mode == NORMAL_MODE && lexer->type_token == T_GENERAL
		&& ft_strchr(lexer->data, ' ') && lexer->data)
	{
		split = ft_split(lexer->data, ' ');
		i = 0;
		while (split[i])
		{
			curr->args = ft_add_arg(curr->args, split[i]);
			i++;
		}
		ft_free_split(split);
	}
	else if (lexer->type_token == T_GENERAL && lexer->data)
		curr->args = ft_add_arg(curr->args, lexer->data);
}

t_parser	*ft_parser(t_lexer *lexer, t_data data)
{
	t_parser	*head;
	t_parser	*curr;
	t_outfile	*last_out;

	last_out = NULL;
	head = NULL;
	curr = NULL;
	while (lexer)
	{
		if (!ft_parse_heredoc(&lexer, &curr))
			continue ;
		if (!ft_parse_pipes(&lexer, &curr))
			continue ;
		ft_check_parser_curr(&curr, &last_out, &head);
		ft_parse_general_token(lexer, curr);
		if (!ft_parse_redirs(&lexer, &curr, &last_out, data))
			continue ;
		lexer = lexer->next;
	}
	return (head);
}
