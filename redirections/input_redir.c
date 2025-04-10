/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:22 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 13:02:16 by jpuerto          ###   ########.fr       */
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
			exit_error("Error opening file input");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_in);
			exit_error("Error in dup2");
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
}
