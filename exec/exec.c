/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:00:42 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 16:36:56 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_path_from_env(char **envp)
{
	int		i;
	char	*path_env;

	i = 0;
	if (!envp[i])
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			return (path_env);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_find_executable(char *command, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*path;
	char	*temp;
	int		i;

	path_env = ft_get_path_from_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_split(paths), NULL);
		path = ft_strjoin(temp, command);
		free(temp);
		if (!path)
			return (ft_free_split(paths), NULL);
		if (access(path, X_OK) == 0)
			return (ft_free_split(paths), path);
		free(path);
	}
	return (ft_free_split(paths), NULL);
}

void	ft_init_pipes(int num_commands, int ***array_pipes, pid_t **array_pids)
{
	int	i;

	*array_pipes = (int **) malloc((num_commands - 1) * sizeof(int *));
	*array_pids = (pid_t *) malloc(num_commands * sizeof(pid_t));
	if (!*array_pipes || !*array_pids)
		return ;
	i = 0;
	while (i < num_commands - 1)
	{
		(*array_pipes)[i] = (int *) malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe((*array_pipes)[i]) == -1)
			ft_exit_error("Error init pipes", NULL, 0);
		i++;
	}
}

void	ft_finish_exec(int num_commands, int ***array_pipes, pid_t **array_pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_commands - 1)
	{
		close((*array_pipes)[i][0]);
		close((*array_pipes)[i][1]);
		i++;
	}
	i = 0;
	while (i < num_commands)
	{
		waitpid((*array_pids)[i], &status, 0);
		i++;
	}
	i = 0;
	while (i < num_commands - 1)
	{
		free((*array_pipes)[i]);
		i++;
	}
	free(*array_pipes);
	free(*array_pids);
}

void	ft_find_path(t_parser *commands, char **envp)
{
	char	*path;

	if (!commands->args)
		return ;
	if (ft_strchr(commands->args[0], '/'))
	{
		if (access(commands->args[0], X_OK) == 0)
			execve(commands->args[0], commands->args, envp);
		else
		{
			ft_exit_error("command not found", NULL, 0);
			ft_free_parser(commands);
			exit(127);
		}
	}
	path = ft_find_executable(commands->args[0], envp);
	if (!path || execve(path, commands->args, envp) == -1)
	{
		ft_free_parser(commands);
		ft_exit_error("command not found", NULL, 0);
		exit(127);
	}
}
