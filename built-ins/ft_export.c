/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:50 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/05 12:36:08 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_is_sort(t_env *current, t_env *next_node)
{
	if (ft_strncmp(current->content, next_node->content,
			ft_strlen(current->content)) > 0)
		return (false);
	return (true);
}

static void	ft_export_sort(t_env *lst)
{
	t_env	*current;
	t_env	*next_node;
	char	*temp_content;
	int		ordered;

	if (lst == NULL || lst == NULL)
		return ;
	ordered = false;
	while (ordered == false)
	{
		ordered = true;
		current = lst;
		while (current != NULL && current->next != NULL)
		{
			next_node = current->next;
			if (!ft_is_sort(current, next_node))
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

static void	ft_print_export(t_env *exports)
{
	t_env	*lst;
	char	*value;

	lst = exports;
	while (lst != NULL)
	{
		value = ft_strchr(lst->content, '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (value && *(value + 1) == '\0')
		{
			ft_putstr_fd(lst->content, STDOUT_FILENO);
			ft_putstr_fd("\"\"", STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else
			ft_putendl_fd(lst->content, STDOUT_FILENO);
		lst = lst->next;
	}
}

static void	ft_free_exports(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->content);
		free(env);
		env = tmp;
	}
}

int	ft_export(char **args, t_data *data)
{
	t_env	*exports;
	t_env	*new_var;

	exports = ft_dup_env(data->env_arr);
	if ((args[0] && !args[1]) || (args[0] && args[1] && !args[1][0]))
	{
		ft_export_sort(exports);
		return (ft_print_export(exports), ft_free_exports(exports), 1);
	}
	args++;
	while (*args)
	{
		if (!ft_check_var(*args, data))
			ft_create_var(&new_var, *args, data);
		args++;
	}
	ft_free_exports(exports);
	return (1);
}
