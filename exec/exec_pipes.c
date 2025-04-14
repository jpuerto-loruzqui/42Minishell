/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 14:30:06 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	manage_signals(t_data *data, int status, pid_t *array_pids)
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
			interrupted = 1;
		i++;
	}
	if (interrupted)
		write(1, "\n", 1);
	signal(SIGINT, sigint_handler);
}

static void	manage_heredoc(t_parser *cmd)
{
	if (cmd->delim)
	{
		signal(SIGINT, SIG_DFL);
		ft_heredoc(cmd->delim, cmd);
	}
}

static void	handle_all_heredocs(t_parser *cmd)
{
	t_parser *tmp = cmd;

	while (tmp)
	{
		manage_heredoc(tmp);
		tmp = tmp->next;
	}
}

static void	manage_commands(t_data *data, t_parser *cmd, int **array_pipes,
	pid_t *array_pids)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_commands)
	{
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
	handle_all_heredocs(cmd);
	manage_commands(data, cmd, array_pipes, array_pids);
	close_all_pipes(data, array_pipes);
	manage_signals(data, status, array_pids);
	finish_exec(data->num_commands, &array_pipes, &array_pids);
}
