/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/13 18:45:26 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_redirs(t_parser *cmd, t_data *data)
{
	int		fd;

	if (!cmd->args && !cmd->delim && !cmd->outfiles)
	{
		data->error = true;
		exit(1);
	}
	if (!cmd->args && cmd->delim && !cmd->outfiles)
		exit(0);
	if ((cmd->outfiles && cmd->outfiles->data && !cmd->args) || (cmd->outfiles
			&& cmd->outfiles->data && cmd->infile && !cmd->args))
	{
		fd = open(cmd->outfiles->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			perror("");
		close(fd);
		exit(1);
	}
	if (cmd->infile && !cmd->args)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			perror("");
		exit(1);
	}
}

void	ft_output_redir(t_parser *commands)
{
	t_outfile	*tmp;
	int			fd_out;

	tmp = commands->outfiles;
	while (tmp != NULL)
	{
		if (tmp->append == true)
			fd_out = open(tmp->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			ft_exit_error("Error opening file output", NULL, 0);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_out);
			ft_free_parser(commands);
			exit(1);
		}
		close(fd_out);
		tmp = tmp->next;
	}
}
