/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 18:15:24 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
