/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/11 10:36:47 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(t_data *data, int **array_pipes)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close(array_pipes[i][0]);
		close(array_pipes[i][1]);
		i++;
	}
}

void	close_unused_pipes(int num_commands, int i, int ***array_pipes)
{
	int	j;

	j = 0;
	while (j < num_commands - 1)
	{
		if (j != i && j != i - 1)
		{
			close((*array_pipes)[j][0]);
			close((*array_pipes)[j][1]);
		}
		j++;
	}
}

void	manage_signals(t_data *data, int status, pid_t *array_pids)
{
	int	i;
	int	interrupted;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	i = 0;
	interrupted = 0;
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
}

void	manage_commands(t_data *data, t_parser *cmd, int **array_pipes,
	pid_t *array_pids)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_commands)
	{
		if (cmd->delim)
		{
			signal(SIGINT, SIG_DFL);
			ft_heredoc(cmd->delim, cmd);
		}
		pid = fork();
		if (pid < 0)
		{
			free_parser(cmd);
			exit_error("Error fork pipes");
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			exec_child(i, &array_pipes, cmd, data);
		}
		else
			array_pids[i] = pid;
		cmd = cmd->next;
		i++;
	}
}

void	exec_pipes(t_data *data)
{
	int			**array_pipes;
	pid_t		*array_pids;
	int			status;
	t_parser	*cmd;

	status = 0;
	cmd = data->commands;
	init_pipes(data->num_commands, &array_pipes, &array_pids);
	manage_commands(data, cmd, array_pipes, array_pids);
	close_all_pipes(data, array_pipes);
	manage_signals(data, status, array_pids);
	finish_exec(data->num_commands, &array_pipes, &array_pids);
}
