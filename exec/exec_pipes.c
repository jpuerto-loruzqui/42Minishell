/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 10:02:07 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_manage_signals(t_data *data, int status, pid_t *array_pids)
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
	signal(SIGINT, ft_sigint_handler);
}

static void	ft_manage_heredoc(t_parser *cmd)
{
	if (cmd->delim)
	{
		signal(SIGINT, SIG_DFL);
		ft_heredoc(cmd->delim, cmd);
	}
}

static void	ft_handle_all_heredocs(t_parser *cmd)
{
	t_parser	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_manage_heredoc(tmp);
		tmp = tmp->next;
	}
}

static void	ft_manage_commands(t_data *data, t_parser *cmd, int **array_pipes,
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
			ft_free_parser(cmd);
			ft_exit_error("Error fork pipes");
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			ft_exec_child(i, &array_pipes, cmd, data);
		}
		else
			array_pids[i] = pid;
		cmd = cmd->next;
		i++;
	}
}

void	ft_exec_pipes(t_data *data)
{
	int			**array_pipes;
	pid_t		*array_pids;
	int			status;
	t_parser	*cmd;

	status = 0;
	cmd = data->commands;
	ft_init_pipes(data->num_commands, &array_pipes, &array_pids);
	ft_handle_all_heredocs(cmd);
	ft_manage_commands(data, cmd, array_pipes, array_pids);
	ft_close_all_pipes(data, array_pipes);
	ft_manage_signals(data, status, array_pids);
	ft_finish_exec(data->num_commands, &array_pipes, &array_pids);
}
