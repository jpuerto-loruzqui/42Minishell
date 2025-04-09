/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/09 19:37:51 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_redir(t_parser *commands)
{
	int	fd_out;

	if (commands->outfile != NULL)
	{
		if (commands->append == true)
			fd_out = open(commands->outfile, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(commands->outfile, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			free_parser(commands);
			exit_error("Error opening file output"); // EXIT ??
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_out);
			free_parser(commands);
			exit_error("Error in dup2"); // EXIT ??
		}
		close(fd_out);
	}
}
