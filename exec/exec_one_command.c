/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 13:07:58 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one_command(t_parser *commands, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: exec one command");
		free_parser(commands);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		input_redir(commands);
		output_redir(commands);
		find_path(commands, envp);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		waitpid(pid, NULL, 0);
	}
}
