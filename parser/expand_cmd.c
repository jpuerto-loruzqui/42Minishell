/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:12:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 19:12:25 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_expansion(int *i, char *token, char **aux)
{
	int		j;
	char	*cmd;
	char	*env_value;
	char	*expanded_value;

	if (token[*i] == '{')
		(*i)++;
	j = *i;
	while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
		j++;
	cmd = ft_substr(token, *i, j - *i);
	if (cmd)
	{
		env_value = getenv(cmd);
		if (env_value)
		{
			expanded_value = ft_strdup(env_value);
			*aux = ft_strjoin_free(*aux, expanded_value);
		}
		free(cmd);
	}
	(*i) = j;
	if (token[*i] == '}')
		i++;
}

char	*expand_cmd(char *token)
{
	char	*aux;
	int		i;

	i = 0;
	aux = "";
	while (token && token[i])
	{
		if (token[i] == '$')
		{
			i++;
			do_expansion(&i, token, &aux);
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
