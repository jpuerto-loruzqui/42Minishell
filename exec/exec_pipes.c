/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/11 10:23:25 by jpuerto          ###   ########.fr       */
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
	t_parser *cmd = data->commands;

	interrupted = 0;
	init_pipes(data->num_commands, &array_pipes, &array_pids);
	i = 0;
	while (i < data->num_commands)
	{
		pid = fork();
		if (pid < 0)
		{
			free_parser(cmd);
			exit_error("Error fork pipes"); // aqui no deberia haber tambien un exit?
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			exec_child(i, &array_pipes, cmd, data);
		}
		else
		{
			array_pids[i] = pid;
		}
		cmd = cmd->next;;
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
		if (WIFEXITED(status))
			data->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->last_exit_code = 128 + WTERMSIG(status);
		else
			data->last_exit_code = 1;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			interrupted = 1;
			write(1, "\n", 1);
		}
		i++;
	}
	if (interrupted)
		write(1, "\n", 1);
	signal(SIGINT, sigint_handler);
	finish_exec(data->num_commands, &array_pipes, &array_pids);
}
