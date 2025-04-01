/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:52 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/27 16:52:53 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_parser *commands, char **envp, int num_commands)
{
	pid_t		pid;
	int			**array_pipes;
	pid_t		*array_pids;
	int			i;

	init_pipes(num_commands, &array_pipes, &array_pids);
	i = 0;
	while (i < num_commands)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("minishell: error fork");
			free_parser(commands);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			exec_child(i, num_commands, &array_pipes, commands, envp);
		else
			array_pids[i] = pid;
		commands = commands->next;
		i++;
	}
	finish_exec(num_commands, &array_pipes, &array_pids);
}
