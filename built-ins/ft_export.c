/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:50 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 19:00:52 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_sort(t_env **lst)
{
	t_env	*current;
	t_env	*next_node;
	char	*temp_content;
	int		ordered;

	if (lst == NULL || *lst == NULL)
		return ;
	ordered = false;
	while (ordered = false)
	{
		ordered = true;
		current = *lst;
		while (current != NULL && current->next != NULL)
		{
			next_node = current->next;
			if (strcmp(current->content, next_node->content) > 0)
			{
				temp_content = current->content;
				current->content = next_node->content;
				next_node->content = temp_content;
				ordered = false;
			}
			current = next_node;
		}
	}
}

void	print_export(t_env *exports)
{
	t_env	*lst;

	lst = exports;
	while (lst != NULL)
	{
		ft_putendl_fd(lst->content, STDERR_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		lst = lst->next;
	}
}

int	ft_export(char **args, t_env *envp)
{
	t_env	*exports;

	exports = ft_dup_env(envp);
	ft_export_sort(&exports);
	if (args[0] && !args[1])
		print_export(exports);
}
