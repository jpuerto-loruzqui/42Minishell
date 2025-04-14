/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 12:19:00 by jpuerto          ###   ########.fr       */
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
	if (((*lexer)->mode != SIMPLE_MODE && ft_strchr((*lexer)->data, '$'))
		&& (ft_isalnum(*(ft_strchr((*lexer)->data, '$') + 1))))
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

void	parse_redirs(t_lexer **lexer, t_parser **curr, t_outfile **last_out)
{
	if ((*lexer)->type_token == T_REDIR_IN && (*lexer)->next)
	{
		(*curr)->infile = ft_strdup((*lexer)->next->data);
		(*lexer) = (*lexer)->next;
	}
	if (((*lexer)->type_token == T_REDIR_OUT
			|| (*lexer)->type_token == T_APPEND)
		&& (*lexer)->next)
	{
		*last_out = append_outfile(&(*curr)->outfiles, new_outfile(*lexer));
		(*lexer) = (*lexer)->next;
	}
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

void	check_parser_curr(t_parser **curr, t_outfile
		**last_out, t_parser **head)
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
