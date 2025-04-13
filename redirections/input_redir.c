/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 14:10:33 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_redir(t_parser *commands)
{
	int	fd_in;

	if (commands->here_fd)
	{
		if (commands->here_fd < 0)
		{
			perror("here_fd");
			exit(1);
		}
		if (dup2(commands->here_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc:");
			close(commands->here_fd);
			exit(1);
		}
		close(commands->here_fd);
		return ;
	}
	if (commands->infile)
	{
		fd_in = open(commands->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("fd");
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("input_redir:");
			close(fd_in);
			exit(1);
		}
		close(fd_in);
	}
}
