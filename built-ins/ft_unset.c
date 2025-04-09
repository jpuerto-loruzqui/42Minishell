/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/09 16:55:15 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_unset(char **args, t_env *envp)
{
	t_env	*current;
	t_env	*temp;
	t_env	*prev;
	int		i;

	current = envp;
	prev = NULL;
	while (current)
	{
		i = 0;
		while (args[i])
		{
			if (strncmp(current->content, args[i], strlen(args[i])) == 0
				&& (current->content[strlen(args[i])] == '='
					|| current->content[strlen(args[i])] == '\0'))
			{
				if (prev)
					prev->next = current->next;
				else
					current = current->next;
				temp = current;
				current = current->next;
				free(temp->content);
				free(temp);
				break ;
			}
			i++;
		}
		if (!args[i])
		{
			prev = current;
			current = current->next;
		}
	}
	return (envp);
}
