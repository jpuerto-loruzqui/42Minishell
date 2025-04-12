/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:01:51 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 10:02:49 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pipes_first_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
    close((*array_pipes)[i][0]);
    if (cmd->outfiles)
	{
        output_redir(cmd);
        close((*array_pipes)[i][1]);
        find_path(cmd, data->env_arr);
    }
    else
	{
        if (dup2((*array_pipes)[i][1], STDOUT_FILENO) == -1)
		{
            close((*array_pipes)[i][1]);
            exit_error("Error in dup2");
            exit(EXIT_FAILURE);
        }
        close((*array_pipes)[i][1]);
        find_path(cmd, data->env_arr);
    }
}

static void pipes_middle_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
    close((*array_pipes)[i][0]);
	close((*array_pipes)[i - 1][1]);

    if (cmd->outfiles)
    {
        if (cmd->infile)
            input_redir(cmd);
        else
        {
            if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
            {
                close((*array_pipes)[i][1]);
                close((*array_pipes)[i - 1][0]);
                exit_error("Error in dup2");
                exit(EXIT_FAILURE);
            }
        }
        output_redir(cmd);
    }
    else
    {
        if (cmd->infile)
            input_redir_last(cmd);
        else
        {
            if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
            {
                close((*array_pipes)[i][1]);
                close((*array_pipes)[i - 1][0]);
                exit_error("Error in dup2");
                exit(EXIT_FAILURE);
            }
        }
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
    find_path(cmd, data->env_arr);

}


static void pipes_last_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
	close((*array_pipes)[i - 1][1]);

    if (cmd->outfiles)
    {
        if (cmd->infile)
            input_redir(cmd);
        else
        {
            if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
            {
                close((*array_pipes)[i - 1][0]);
                exit_error("Error in dup2 (stdin)");
                exit(EXIT_FAILURE);
            }
        }
        output_redir(cmd);
    }
    else
    {
        if (cmd->infile)
            input_redir_last(cmd);
        else
        {
            if (dup2((*array_pipes)[i - 1][0], STDIN_FILENO) == -1)
            {
                close((*array_pipes)[i - 1][0]);
                exit_error("Error in dup2 (stdin)");
                exit(EXIT_FAILURE);
            }
        }
    }
    close((*array_pipes)[i - 1][0]);
    find_path(cmd, data->env_arr);
}

void    exec_child(int i, int ***array_pipes, t_parser *cmd, t_data *data)
{
    close_unused_pipes(data->num_commands, i, array_pipes);
    if (i == 0)
    {
        if (data->delim)
		{
            signal(SIGINT, SIG_DFL);
			ft_heredoc(data->delim, cmd);
			input_redir(cmd);
			pipes_first_child(i, array_pipes, cmd, data);
		}
        else
            check_redirs(cmd, data);
		input_redir(cmd);
		pipes_first_child(i, array_pipes, cmd, data);
    }
    else if (i == data->num_commands - 1)
	{
		pipes_last_child(i, array_pipes, cmd, data);
	}
    else 
		pipes_middle_child(i, array_pipes, cmd, data);
}
