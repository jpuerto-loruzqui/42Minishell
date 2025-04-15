/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/15 21:58:10 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_expand(t_lexer **lexer, t_data data)
{
	if ((*lexer)->mode != SIMPLE_MODE
		&& ft_strncmp("$?", (*lexer)->data, 3) == 0)
	{
		free((*lexer)->data);
		(*lexer)->data = ft_itoa(data.last_exit_code);
	}
	if (((*lexer)->mode != SIMPLE_MODE && ft_strchr((*lexer)->data, '$')))
	{
		(*lexer)->data = expand_cmd((*lexer)->data, data.env_arr);
		if ((*lexer)->data == NULL)
		{
			free((*lexer)->data);
			(*lexer) = (*lexer)->next;
			return (0);
		}
	}
	return (1);
}

int	parse_redirs(t_lexer **lexer, t_parser **curr, t_outfile **last_out,
	t_data data)
{
	if ((*lexer)->type_token == T_REDIR_IN && (*lexer)->next
		&& (*lexer)->next->type_token == T_GENERAL)
	{
		if ((*curr)->infile)
			free((*curr)->infile);
		(*curr)->infile = ft_strdup((*lexer)->next->data);
		(*lexer) = (*lexer)->next;
		if ((*lexer))
			(*lexer)->type_token = T_INFILE;
		return (0);
	}
	if (((*lexer)->type_token == T_REDIR_OUT
			|| (*lexer)->type_token == T_APPEND)
		&& (*lexer)->next)
	{
		*last_out = append_outfile(&(*curr)->outfiles,
				new_outfile(*lexer, data));
		(*lexer) = (*lexer)->next;
		if ((*lexer))
			(*lexer)->type_token = T_OUTFILE;
		return (0);
	}
	return (1);
}

int	parse_heredoc(t_lexer **lexer, t_parser **curr)
{
	if ((*lexer)->prev != NULL && (*lexer)->prev->type_token == T_HEREDOC
		&& (*lexer)->type_token == T_GENERAL)
	{
		(*curr)->delim = ft_strdup((*lexer)->data);
		(*lexer) = (*lexer)->next;
		return (0);
	}
	return (1);
}

void	check_parser_curr(t_parser **curr, t_outfile **last_out,
	t_parser **head)
{
	if (!(*curr))
	{
		(*curr) = new_node();
		add_node(head, (*curr));
		if (last_out != NULL)
			(*curr)->last_outfile = *last_out;
	}
}

int	parse_pipes(t_lexer **lexer, t_parser **curr)
{
	if ((*lexer)->type_token == T_PIPE)
	{
		(*curr) = NULL;
		(*lexer) = (*lexer)->next;
		return (0);
	}
	return (1);
}
