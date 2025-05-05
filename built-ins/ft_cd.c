/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/23 16:39:45 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_cd(t_data *data, char *export_str, char *newpwd)
{
	ft_free_split(data->env_arr);
	free(export_str);
	free(newpwd);
}

static int	ft_control_cd(char **path, char **args, t_data *data)
{
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0
		|| ft_strncmp(args[1], "-", 2) == 0)
	{
		if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
			*path = ft_getenv("HOME", data->env_arr);
		else if (ft_strncmp(args[1], "-", 2) == 0)
			*path = ft_getenv("OLDPWD", data->env_arr);
		if (!*path)
		{
			printf("minishell: cd: variable not set\n");
			return (1);
		}
	}
	else
	{
		if (args[2])
		{
			printf("cd: usage: cd <path>\n");
			return (1);
		}
		*path = args[1];
	}
	return (0);
}

static void	ft_free_old_and_export(char *export_str, char *oldpwd)
{
	free(export_str);
	free(oldpwd);
}

int	ft_cd(char **args, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;
	char	*export_str;
	char	*path;

	if (ft_control_cd(&path, args, data))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("minishell: getcwd"), 1);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), free(oldpwd),
			data->last_exit_code = 126, 1);
	export_str = ft_strjoin("OLDPWD=", oldpwd);
	ft_export((char *[]){"export", export_str, NULL}, data);
	ft_free_old_and_export(export_str, oldpwd);
	newpwd = getcwd(NULL, 0);
	data->pwd = newpwd;
	if (!newpwd)
		return (perror("minishell: getcwd"), 1);
	export_str = ft_strjoin("PWD=", newpwd);
	ft_export((char *[]){"export", export_str, NULL}, data);
	ft_free_cd(data, export_str, newpwd);
	data->env_arr = ft_lsttoa(*data);
	return (0);
}
