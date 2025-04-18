/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:12:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 16:59:08 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_do_expansion(int *i, char *token, char **env_arr)
{
	int		j;
	char	*cmd;
	char	*env_value;
	char	*expanded_value;
	char	*aux;

	aux = "";
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
			aux = ft_strjoin_free(aux, expanded_value);
		}
		free(cmd);
	}
	(*i) = j;
	if (!aux[0])
		aux = ft_strdup("");
	return (aux);
}

char	*ft_expand_cmd(char *token, char **env_arr)
{
	int		i;
	char	*aux;

	aux = ft_strdup("");
	i = 0;
	while (token && token[i])
	{
		if (token[i] == '$' && token[i + 1])
		{
			i++;
			free(aux);
			aux = ft_do_expansion(&i, token, env_arr);
		}
		else
		{
			aux = ft_append_char(aux, token[i]);
			i++;
		}
	}
	return (aux);
}
