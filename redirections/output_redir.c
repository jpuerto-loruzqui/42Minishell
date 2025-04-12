/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 10:55:02 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_redirs(t_parser *cmd, t_data *data)
{
    int fd;
	char *argv[2];
    
    argv[0] = "true";
    argv[1] = NULL;
    
    if ((cmd->outfiles && cmd->outfiles->data&& !cmd->args)
    || (cmd->outfiles && cmd->outfiles->data
    && !cmd->args && cmd->infile && !cmd->args))
    {
        fd = open(cmd->outfiles->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd >= 0)
            close(fd);
        execve("/bin/true", argv, data->env_arr);	
        perror("execve");
    }
	if (cmd->infile && !cmd->args)
	{
		execve("/bin/true", argv, data->env_arr);	
		perror("execve");
	}
}

void output_redir(t_parser *commands)
{
    t_outfile *tmp;
    int fd_out;

    tmp = commands->outfiles;
    while (tmp != NULL) 
    {
        if (tmp->append == true)
            fd_out = open(tmp->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0)
        {
            free_parser(commands);
            exit_error("Error opening file output");
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            close(fd_out);
            free_parser(commands);
            exit_error("Error in dup2");
        }
        close(fd_out);
        tmp = tmp->next;
    }
}



