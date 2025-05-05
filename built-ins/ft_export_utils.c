/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:42:05 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/05 09:50:34 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_create_var(t_env **new_var, char *args, t_data *data)
{
	char	*var;
	int		i;

	i = 0;
	while (args[i] && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	if ((!ft_isalpha(args[0]) && args[0] != '_')
		|| (args[i] != '=' && args[i] != '\0' ))
	{
		data->error = true;
		data->last_exit_code = 1;
		return (ft_putstr_fd("Not identifier: ", 2), ft_putendl_fd(args, 2));
	}
	var = ft_substr(args, 0, i);
	if (args[i] == '=')
	{
		var = ft_append_char(var, '=');
		i++;
		while (args[i])
			var = ft_append_char(var, args[i++]);
	}
	else
		var = ft_append_char(var, '=');
	(*new_var) = ft_new_node_env(var);
	ft_envadd_back(&data->env, *new_var);
	free(var);
}

int	ft_check_var(char *arg, t_data *data)
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
