/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 09:53:49 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_cd(t_data *data, char *export_str, char *newpwd)
{
	ft_free_split(data->env_arr);
	free(export_str);
	free(newpwd);
}

static int	ft_control_cd(char **path, char **args, t_data *data)
{
	if (args[2])
	{
		printf("cd: usage: cd <path>\n");
		return (1);
	}
	if (!args[1])
	{
		*path = ft_getenv("HOME", data->env_arr);
		if (!*path)
		{
			printf("minishell: cd: HOME variable not set\n");
			return (1);
		}
	}
	else
		*path = args[1];
	return (0);
}

int	ft_cd(char **args, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;
	char	*export_str;
	int		dir_res;
	char	*path;

	if (ft_control_cd(&path, args, data))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("minishell: getcwd"), 1);
	dir_res = chdir(path);
	if (dir_res == -1)
		return (perror("minishell: cd"), free(oldpwd), 1);
	export_str = ft_strjoin("OLDPWD=", oldpwd);
	ft_export((char *[]){"export", export_str, NULL}, data);
	free(export_str);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("minishell: getcwd"), 1);
	export_str = ft_strjoin("PWD=", newpwd);
	ft_export((char *[]){"export", export_str, NULL}, data);
	free_cd(data, export_str, newpwd);
	data->env_arr = ft_lsttoa(*data);
	return (0);
}
