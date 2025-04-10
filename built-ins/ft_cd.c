/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 20:16:45 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void free_cd(t_data *data, char *export_str, char *newpwd)
{
	ft_free_split(data->env_arr);
	free(export_str);
	free(newpwd);
}

int	ft_cd(char **args, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;
	char	*export_str;
	int		dir_res;

	if (!args[1] || args[2])
		return (printf("cd: usage: cd <path>\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("minishell: getcwd"), 1);
	dir_res = chdir(args[1]);
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
	data->env_arr = ft_lsttoa(*data);
	free_cd(data, export_str, newpwd);
	return (0);
}


