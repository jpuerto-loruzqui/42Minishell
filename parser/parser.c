/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 11:40:28 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*new_node(void)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->infile = NULL;
	node->outfiles = NULL;
	node->next = NULL;
	node->last_outfile = NULL;
	node->delim = NULL;
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

t_outfile	*append_outfile(t_outfile **head, t_outfile *new)
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

t_outfile	*new_outfile(t_lexer *lexer)
{
	t_outfile	*node;

	node = malloc(sizeof(t_outfile));
	if (!node)
		return (NULL);
	node->append = (lexer->type_token == T_APPEND);
	if (lexer->next->data)
		node->data = ft_strdup(lexer->next->data);
	else
		node->data = NULL;
	node->next = NULL;
	return (node);
}

t_parser	*parser(t_lexer *lexer, t_data data)
{
	t_parser	*head;
	t_parser	*curr;
	t_outfile	*last_out;
	
	last_out = NULL;
	head = NULL;
	curr = NULL;
	while (lexer)
	{			
		if (lexer->mode != SIMPLE_MODE && ft_strncmp("$?", lexer->data, 3) == 0)
		{
			free(lexer->data);
			lexer->data = ft_itoa(data.last_exit_code);
		}
		if ((lexer->mode != SIMPLE_MODE && ft_strchr(lexer->data, '$'))
			&& (ft_isalnum(*(ft_strchr(lexer->data, '$') + 1))
				|| !ft_strncmp(ft_strchr(lexer->data, '$') + 1, "{", 1)))
		{
			lexer->data = expand_cmd(lexer->data, data.env_arr);
			if (lexer->data == NULL)
			{
				free(lexer->data);
				lexer = lexer->next;
				continue ;
			}
		}
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
			if (last_out != NULL)
				curr->last_outfile = last_out;
		}
		if (lexer->prev != NULL && lexer->prev->type_token == T_HEREDOC && lexer->type_token == T_GENERAL)
		{
			curr->delim =  ft_strdup(lexer->data);
			lexer = lexer->next;
			continue ;
		}
		if (lexer->type_token == T_GENERAL && lexer->data)
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
			last_out = append_outfile(&curr->outfiles, new_outfile(lexer));
			lexer = lexer->next;
		}
		lexer = lexer->next;
	}
	return (head);
}
