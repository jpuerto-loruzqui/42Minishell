/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui < >                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 17:17:44 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_found_var(t_env *current, int i, char **args)
{
	if (ft_strncmp(current->content, args[i], ft_strlen(args[i])) == 0
		&& (current->content[ft_strlen(args[i])] == '='
			|| current->content[ft_strlen(args[i])] == '\0'))
		return (true);
	return (false);
}

static void	ft_delete_var(t_env **envp, t_env *prev, t_env **current)
{
	t_env	*temp;

	if (prev)
		prev->next = (*current)->next;
	else
		*envp = (*current)->next;
	temp = *current;
	*current = (*current)->next;
	free(temp->content);
	free(temp);
}

t_env	*ft_unset(char **args, t_env *envp)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	current = envp;
	prev = NULL;
	while (current)
	{
		i = 0;
		while (args[i])
		{
			if (ft_strncmp(args[i], "PWD", 4) == 0)
			{
				ft_exit_error("minishell: cannot unset this variable", NULL, 0);
				return (envp);
			}
			if (ft_found_var(current, i, args))
			{
				ft_delete_var(&envp, prev, &current);
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
