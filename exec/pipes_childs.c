/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:01:51 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 12:25:33 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pipes_first_child(int i, int ***array_pipes, t_parser *cmd)
{
    close((*array_pipes)[i][0]);
    if (!cmd->outfiles)
    {
        if (dup2((*array_pipes)[i][1], STDOUT_FILENO) == -1)
        {
            close((*array_pipes)[i][1]);
            exit_error("Error in dup2");
            exit(EXIT_FAILURE);
        }
    }
    close((*array_pipes)[i][1]);
}

static void pipes_middle_child(int i, int ***array_pipes, t_parser *cmd)
{
    close((*array_pipes)[i][0]);
	close((*array_pipes)[i - 1][1]);
    if (!cmd->infile)
    {
        if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
        {
            close((*array_pipes)[i][1]);
            close((*array_pipes)[i - 1][0]);
            exit_error("Error in dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (!cmd->outfiles)
    {
        if (dup2((*array_pipes)[i][1], STDOUT_FILENO) == -1)
        {
            close((*array_pipes)[i][1]);
            close((*array_pipes)[i - 1][0]);
            exit_error("Error in dup2");
            exit(EXIT_FAILURE);
        }
    }
    close((*array_pipes)[i][1]);
    close((*array_pipes)[i - 1][0]);
}

static void pipes_last_child(int i, int ***array_pipes, t_parser *cmd)
{
	close((*array_pipes)[i - 1][1]);

    if (!cmd->infile)
    {
        if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
        {
            close((*array_pipes)[i - 1][0]);
            exit_error("Error in dup2");
            exit(EXIT_FAILURE);
        }
    }
    close((*array_pipes)[i - 1][0]);
}

void    exec_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
    close_unused_pipes(data->num_commands, i, array_pipes);
    input_redir(cmd);
    output_redir(cmd);
    if (i == 0)
    {
		pipes_first_child(i, array_pipes, cmd);
    }
    else if (i == data->num_commands - 1)
		pipes_last_child(i, array_pipes, cmd);
    else 
		pipes_middle_child(i, array_pipes, cmd);
    check_redirs(cmd, data);
    find_path(cmd, data->env_arr);
}
