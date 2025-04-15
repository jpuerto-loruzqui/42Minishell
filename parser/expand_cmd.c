/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:12:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/15 11:28:14 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	do_expansion(int *i, char *token, char **aux, char **env_arr)
{
	int		j;
	char	*cmd;
	char	*env_value;
	char	*expanded_value;

	j = *i;
	while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
		j++;
	cmd = ft_substr(token, *i, j - *i);
	if (cmd)
	{
		env_value = ft_getenv(cmd, env_arr);
		if (env_value)
		{
			expanded_value = ft_strdup(env_value);
			*aux = ft_strjoin_free(*aux, expanded_value);
		}
		free(cmd);
	}
	(*i) = j;
}

char	*expand_cmd(char *token, char **env_arr)
{
	char	*aux;
	int		i;

	i = 0;
	aux = "";
	while (token && token[i])
	{
		if (token[i] == '$' && token[i + 1])
		{
			i++;
			do_expansion(&i, token, &aux, env_arr);
		}
		else
		{
			aux = append_char(aux, token[i]);
			i++;
		}
	}
	free(token);
	return (aux);
}
