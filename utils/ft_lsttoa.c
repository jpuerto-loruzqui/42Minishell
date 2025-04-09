/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:11:49 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 13:23:22 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_envsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**ft_lsttoa(t_data data)
{
	int		size;
	int		i;

	i = 0;
	size = ft_envsize(data.env);
	data.env_arr = malloc(sizeof(char *) * (size + 1));
	while (data.env != NULL)
	{
		data.env_arr[i] = ft_strdup(data.env->content);
		i++;
		data.env = data.env->next;
	}
	data.env_arr[i] = NULL;
	return (data.env_arr);
}
