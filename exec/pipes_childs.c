/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:01:51 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/05 09:58:28 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipes_first_child(int i, int ***array_pipes, t_parser *cmd)
{
	close((*array_pipes)[i][0]);
	if (!cmd->outfiles)
	{
		if (dup2((*array_pipes)[i][1], STDOUT_FILENO) == -1)
		{
			close((*array_pipes)[i][1]);
			exit(EXIT_FAILURE);
		}
	}
	close((*array_pipes)[i][1]);
}

static void	ft_pipes_middle_child(int i, int ***array_pipes, t_parser *cmd)
{
	close((*array_pipes)[i][0]);
	close((*array_pipes)[i - 1][1]);
	if (!cmd->infile && !cmd->here_fd)
	{
		if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
		{
			close((*array_pipes)[i][1]);
			close((*array_pipes)[i - 1][0]);
			exit(EXIT_FAILURE);
		}
	}
	if (!cmd->outfiles)
	{
		if (dup2((*array_pipes)[i][1], STDOUT_FILENO) == -1)
		{
			close((*array_pipes)[i][1]);
			close((*array_pipes)[i - 1][0]);
			exit(EXIT_FAILURE);
		}
	}
	close((*array_pipes)[i][1]);
	close((*array_pipes)[i - 1][0]);
}

static void	ft_pipes_last_child(int i, int ***array_pipes, t_parser *cmd)
{
	close((*array_pipes)[i - 1][1]);
	if (!cmd->infile && !cmd->here_fd)
	{
		if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
		{
			close((*array_pipes)[i - 1][0]);
			exit(EXIT_FAILURE);
		}
	}
	close((*array_pipes)[i - 1][0]);
}

void	ft_exec_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
	ft_close_unused_pipes(data->num_commands, i, array_pipes);
	ft_input_redir(cmd);
	ft_output_redir(cmd);
	if (i == 0)
		ft_pipes_first_child(i, array_pipes, cmd);
	else if (i == data->num_commands - 1)
		ft_pipes_last_child(i, array_pipes, cmd);
	else
		ft_pipes_middle_child(i, array_pipes, cmd);
	ft_check_redirs(cmd, data);
	if (!ft_is_built_in(cmd, data))
		ft_find_path(cmd, data->env_arr);
	else
	{
		if (data->error == false)
		{
			data->last_exit_code = 0;
			exit(0);
		}
		else
			exit(data->last_exit_code);
	}
}
