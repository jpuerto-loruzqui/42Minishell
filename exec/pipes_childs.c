/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:01:51 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/29 18:01:53 by loruzqui         ###   ########.fr       */
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

void	exec_child(int i, int num_commands, int ***array_pipes,
		t_parser *commands, char **envp)
{
	close_unused_pipes(num_commands, i, array_pipes);
	if (i == 0)
	{
		input_redir(commands);
		pipes_first_child(i, array_pipes);
	}
	else if (i == num_commands - 1)
	{
		output_redir(commands);
		pipes_last_child(i, array_pipes);
	}
	else
		pipes_middle_child(i, array_pipes);
	find_path(commands, envp);
}
