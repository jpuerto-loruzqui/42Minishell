/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 13:22:56 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_data *data)
{
	pid_t		pid;
	int			**array_pipes;
	pid_t		*array_pids;
	int			i;
	int			status;
	int			interrupted;

	interrupted = 0;
	init_pipes(data->num_commands, &array_pipes, &array_pids);
	i = 0;
	while (i < data->num_commands)
	{
		pid = fork();
		if (pid < 0)
		{
			free_parser(data->commands);
			exit_error("Error fork pipes");
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			exec_child(i, &array_pipes, data);
		}
		else
		{
			array_pids[i] = pid;
		}
		data->commands = data->commands->next;
		i++;
	}
	i = 0;
	while (i < data->num_commands - 1)
	{
		close(array_pipes[i][0]);
		close(array_pipes[i][1]);
		i++;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	i = 0;
	while (i < data->num_commands)
	{
		waitpid(array_pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			interrupted = 1;
		i++;
	}
	if (interrupted)
		write(1, "\n", 1);
	signal(SIGINT, sigint_handler);
	finish_exec(data->num_commands, &array_pipes, &array_pids);
}
