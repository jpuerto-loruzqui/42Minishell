/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/09 10:40:52 by loruzqui         ###   ########.fr       */
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

static int	ft_process_unset_node(char **args, t_env **envp, t_env **current,
	t_env **prev)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "PWD", 4) == 0)
		{
			ft_exit_error("minishell: cannot unset this variable", NULL, 0);
			return (1);
		}
		if (ft_found_var(*current, i, args))
		{
			ft_delete_var(envp, *prev, current);
			return (0);
		}
		i++;
	}
	if (!args[i])
	{
		*prev = *current;
		*current = (*current)->next;
	}
	return (0);
}

t_env	*ft_unset(char **args, t_env *envp)
{
	t_env	*current;
	t_env	*prev;

	current = envp;
	prev = NULL;
	while (current)
	{
		if (ft_process_unset_node(args, &envp, &current, &prev))
			return (envp);
	}
	return (envp);
}
