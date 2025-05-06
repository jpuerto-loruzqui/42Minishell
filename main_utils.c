/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:24:09 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/06 18:16:11 by loruzqui         ###   ########.fr       */
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

bool	ft_error_tokens(t_data *data)
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

void	ft_update_shlvl(char ***env)
{
	char	*lvl_str;
	int		lvl;
	char	*new_lvl;
	char	*new_entry;

	lvl_str = ft_getenv("SHLVL", *env);
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
	else
		lvl = 0;
	lvl++;
	new_lvl = ft_itoa(lvl);
	new_entry = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	ft_export_env(env, "SHLVL=", new_entry);
}

char	*ft_get_prompt(t_data *data)
{
	char	*cwd;
	char	*colored;
	char	*final;

	cwd = ft_control_getcwd(data);
	colored = ft_strjoin("\001\033[0;32m\002", cwd);
	final = ft_strjoin(colored, COLOR_USERS " minishell> \001\033[0m\002");
	free(colored);
	data->prompt = final;
	free(cwd);
	return (data->prompt);
}
