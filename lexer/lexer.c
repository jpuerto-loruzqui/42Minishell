/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:54:04 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/06 11:34:33 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_get_type_of_delimiter(char *token, t_token *type, t_data *data)
{
	if (ft_strncmp(token, "|", 2) == 0)
		*type = T_PIPE;
	else if (ft_strncmp(token, "<<", 3) == 0)
	{
		data->last_token_type = T_HEREDOC;
		*type = T_HEREDOC;
	}
	else if (ft_strncmp(token, ">>", 3) == 0)
		*type = T_APPEND;
	else if (ft_strncmp(token, "<", 2) == 0)
		*type = T_REDIR_IN;
	else if (ft_strncmp(token, ">", 2) == 0)
		*type = T_REDIR_OUT;
}

t_lexer	*ft_lexer(t_data *data)
{
	t_lexer	*lexer_lst;
	char	*token;
	int		index;
	int		mode;
	t_token	type;

	mode = NORMAL_MODE;
	lexer_lst = NULL;
	index = 0;
	token = ft_strtok(data->input, &mode, data);
	while (token)
	{
		type = T_GENERAL;
		ft_get_type_of_delimiter(token, &type, data);
		if (ft_strncmp(token, " ", 2) != 0)
			ft_add_tok(&lexer_lst, ft_new_tok(index++, token, type, &mode));
		mode = NORMAL_MODE; // hay que probar cosas por esto
		token = ft_strtok(NULL, &mode, data);
		if (data->error)
			return (ft_free_lexer(lexer_lst), NULL);
	}
	return (lexer_lst);
}
