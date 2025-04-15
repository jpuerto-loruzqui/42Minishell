/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 19:44:27 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	manage_heredoc(t_parser *commands)
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
}

static void	manage_infile(t_parser *commands)
{
	int	fd_in;

	fd_in = open(commands->infile, O_RDONLY);
	if (fd_in < 0)
	{
		perror("");
		exit(1);
	}
	else if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("input_redir:");
		close(fd_in);
		exit(1);
	}
	close(fd_in);
}

void	input_redir(t_parser *commands)
{
	if (commands->here_fd)
	{
		manage_heredoc(commands);
		return ;
	}
	if (commands->infile)
	{
		manage_infile(commands);
	}
}
