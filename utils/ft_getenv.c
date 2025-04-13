/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:15:03 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 15:58:16 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(const char *cmd, char **env_arr)
{
	int		i;
	size_t	cmd_len;

	if (!cmd || !env_arr)
		return (NULL);
	cmd_len = ft_strlen(cmd);
	i = 0;
	while (env_arr[i])
	{
		if (ft_strncmp(env_arr[i], cmd, cmd_len) == 0
			&& env_arr[i][cmd_len] == '=')
			return (env_arr[i] + cmd_len + 1);
		i++;
	}
	return (NULL);
}
