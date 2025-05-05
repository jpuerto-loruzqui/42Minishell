/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:24:09 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/23 18:38:49 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_control_getcwd(t_data *data)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: getcwd");
		tmp = ft_getenv("OLDPWD", data->env_arr);
		if (tmp)
			cwd = ft_strdup(tmp);
		else
			cwd = ft_strdup("~");
	}
	return (cwd);
}

bool	error_tokens(t_data *data)
{
	t_lexer	*tok;

	tok = data->tokens;
	while (tok)
	{
		if (tok->type_token == T_REDIR_IN && tok->next
			&& tok->next->type_token != T_INFILE)
			return (true);
		else if (tok->type_token == T_REDIR_OUT && tok->next
			&& tok->next->type_token != T_OUTFILE)
			return (true);
		else if (tok->type_token == T_APPEND && tok->next
			&& tok->next->type_token != T_OUTFILE)
			return (true);
		else if (tok->type_token == T_HEREDOC && tok->next
			&& tok->next->type_token != T_GENERAL)
			return (true);
		else if ((tok->type_token == T_PIPE || tok->type_token == T_HEREDOC
				|| tok->type_token == T_APPEND || tok->type_token == T_REDIR_OUT
				|| tok->type_token == T_REDIR_IN) && !tok->next)
			return (true);
		tok = tok->next;
	}
	return (false);
}
