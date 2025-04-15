/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 20:07:37 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	manage_signals(t_data *data, pid_t pid)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_code = 128 + WTERMSIG(status);
	else
		data->last_exit_code = 1;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	signal(SIGINT, sigint_handler);
}

void	exec_one_command(t_data *data)
{
	pid_t	pid;
	pid = fork();
	if (pid < 0)
	{
		free_parser(data->commands);
		exit_error("Error fork one command");
	}
	else if (pid == 0)
	{
		if (data->commands->delim)
		{
			signal(SIGINT, SIG_DFL);
			ft_heredoc(data->commands->delim, data->commands);
		}
		check_redirs(data->commands, data);
		input_redir(data->commands);
		output_redir(data->commands);
		find_path(data->commands, data->env_arr);
	}
	else
		manage_signals(data, pid);
}
