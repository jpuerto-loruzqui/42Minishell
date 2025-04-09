/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/09 23:18:38 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int	ft_cd(char **args)
{
	char *path;

	if (args[2])
	{
		printf("cd: usage: cd <path>\n");
		return (1);
	}
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME variable not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}*/

int ft_cd(char **args, t_data *data)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*oldpwd_var;
	char	*pwd_var;
	t_env	*new_var;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME variable not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (args[2])
	{
		printf("cd: usage: cd <path>\n");
		return (1);
	}
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	printf("old pwd: %s\n", old_pwd);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!oldpwd_var)
	{
		perror("minishell: cd: ft_strjoin");
		return (1);
	}
	if (check_var(oldpwd_var, data) == 0)
		create_var(&new_var, oldpwd_var, data);
	free(oldpwd_var);
	pwd_var = ft_strjoin("PWD=", new_pwd);
	if (!pwd_var)
	{
		perror("minishell: cd: ft_strjoin");
		return (1);
	}
	if (check_var(pwd_var, data) == 0)
		create_var(&new_var, pwd_var, data);
	free(pwd_var);
	return (0);
}
