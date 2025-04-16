/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 10:06:14 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_get_type_of_delimiter(char *token, t_token *type, t_data *data)
{
	if (ft_strncmp(token, "|", 1) == 0)
		*type = T_PIPE;
	else if (ft_strncmp(token, "<<", 2) == 0)
	{
		data->last_token_type = T_HEREDOC;
		*type = T_HEREDOC;
	}
	else if (ft_strncmp(token, ">>", 2) == 0)
		*type = T_APPEND;
	else if (ft_strncmp(token, "<", 1) == 0)
		*type = T_REDIR_IN;
	else if (ft_strncmp(token, ">", 1) == 0)
		*type = T_REDIR_OUT;
}

t_lexer	*ft_lexer(t_data *data)
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
		ft_get_type_of_delimiter(token, &type, data);
		if (token)
		{
			if (token[0])
				ft_add_token(&lexer_list, ft_new_token(index++, token, type, &mode));
			free(token);
		}
		token = ft_strtok(NULL, &mode, data);
		if (data->error)
			return (ft_free_lexer(lexer_list), NULL);
	}
	return (lexer_list);
}
