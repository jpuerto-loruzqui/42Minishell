/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:01:51 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 18:34:12 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipes_first_child(int i, int ***array_pipes)
{
	close((*array_pipes)[i][0]);
	dup2((*array_pipes)[i][1], STDOUT_FILENO);
	close((*array_pipes)[i][1]);
}

static void	pipes_last_child(int i, int ***array_pipes)
{
	close((*array_pipes)[i - 1][1]);
	dup2((*array_pipes)[i - 1][0], STDIN_FILENO);
	close((*array_pipes)[i - 1][0]);
}

static void	pipes_middle_child(int i, int ***array_pipes)
{
	close((*array_pipes)[i][0]);
	close((*array_pipes)[i - 1][1]);
	dup2((*array_pipes)[i - 1][0], STDIN_FILENO);
	dup2((*array_pipes)[i][1], STDOUT_FILENO);
	close((*array_pipes)[i][1]);
	close((*array_pipes)[i - 1][0]);
}

void	exec_child(int i, int ***array_pipes, t_data *data)
{
	close_unused_pipes(data->num_commands, i, array_pipes);
	if (i == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (data->delim)
			ft_heredoc(data->delim);
		else
			input_redir(data->commands);
		pipes_first_child(i, array_pipes);
	}
	else if (i == data->num_commands - 1)
	{
		output_redir(data->commands);
		pipes_last_child(i, array_pipes);
	}
	else
		pipes_middle_child(i, array_pipes);
	find_path(data->commands, data->env);
}
