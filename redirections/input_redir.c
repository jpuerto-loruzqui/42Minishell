/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/11 15:55:22 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_redir_last(t_parser *commands)
{
	int	fd_in;

	if (commands->last_outfile && commands->last_outfile->data)
	{
		fd_in = open(commands->last_outfile->data, O_RDONLY);
		if (fd_in < 0)
		{
			perror(commands->last_outfile->data);
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd_in);
			exit(1);
		}
		close(fd_in);
	}
}


void	input_redir(t_parser *commands)
{
	int	fd_in;

	if (commands->infile != NULL)
	{
		fd_in = open(commands->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror(commands->infile);
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd_in);
			exit(1);
		}
		close(fd_in);
	}
}
