/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:50 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/09 23:16:57 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_sort(t_env *lst)
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
			if (ft_strncmp(current->content, next_node->content, ft_strlen(next_node->content)) > 0)
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
	char	*value;

	lst = exports;
	while (lst != NULL)
	{
		value = ft_strchr(lst->content, '=');
		if (value && *(value + 1) == '\0')
		{
			ft_putstr_fd(lst->content, STDERR_FILENO);
			ft_putstr_fd("\'\'", STDERR_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else
			ft_putendl_fd(lst->content, STDERR_FILENO);
		lst = lst->next;
	}
}

void	free_exports(t_env *env)
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

void	create_var(t_env **new_var, char *args, t_data *data)
{
	char	*var;
	int		i;

	i = 0;
	while (args[i] && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	if ((!ft_isalpha(args[0]) && args[0] != '_') || (args[i] != '=' && args[i] != '\0'))
		return (ft_putstr_fd("export: Not an identifier: ", 2), ft_putendl_fd(args, 2));
	var = ft_substr(args, 0, i);
	var = append_char(var, '=');
	while (args[i])
		var = append_char(var, args[i++]);
	(*new_var) = new_node_env(var);
	ft_envadd_back(&data->env, *new_var);
	free(var);
}

int	check_var(char *arg, t_data *data)
{
	t_env	*tmp;
	int		i;

	tmp = data->env;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, arg, i) == 0 && !arg[i])
			return (1);
		if (ft_strncmp(tmp->content, arg, i) == 0 && tmp->content[i] == '=')
		{
			free(tmp->content);
			tmp->content = ft_strdup(arg);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(char **args, t_data *data)
{
	t_env	*exports;
	t_env	*new_var;

	exports = ft_dup_env(data->env_arr);
	ft_export_sort(exports);
	if (args[0] && !args[1])
		return (print_export(exports), free_exports(exports), 1);
	args++;
	while (*args)
	{
		if (!check_var(*args, data))
			create_var(&new_var, *args, data);
		args++;
	}
	free_exports(exports);
	return (1);
}
