/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:12:23 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/05 10:00:30 by jpuerto          ###   ########.fr       */
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
	char	*tmp;
	char	*tmp2;

	aux = ft_strdup("");
	i = 0;
	while (token && token[i])
	{
		if (token[i] == '$' && token[i + 1] && ft_isalpha(token[i + 1]))
		{
			i++;
			tmp = ft_do_expansion(&i, token, env_arr);
			tmp2 = ft_strjoin(aux, tmp);
			free(tmp);
			free(aux);
			aux = tmp2;
		}
		else
		{
			aux = ft_append_char(aux, token[i]);
			i++;
		}
	}
	return (aux);
}
