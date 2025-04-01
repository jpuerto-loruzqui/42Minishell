/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/31 16:12:34 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_redir(t_parser *commands)
{
	int	fd_out;

	if (commands->outfile != NULL)
	{
		fd_out = open(commands->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("minishell: error opening file output");
			free_parser(commands);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: error in dup2");
			close(fd_out);
			free_parser(commands);
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}
