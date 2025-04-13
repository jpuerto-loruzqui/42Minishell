/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 21:51:17 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*redir_builtin(t_parser *commands)
{
	int	*std_inout;

	std_inout = malloc(sizeof(int) * 2);
	if (!std_inout)
		return (NULL);
	std_inout[0] = dup(STDIN_FILENO);
	std_inout[1] = dup(STDOUT_FILENO);
	if (commands->infile)
		input_redir(commands);
	if (commands->outfiles)
		output_redir(commands);
	return (std_inout);
}

void	unset_std(int *std_inout)
{
	if (!std_inout)
		return ;
	if (dup2(std_inout[0], STDIN_FILENO) == -1)
	{
		close(std_inout[0]);
		close(std_inout[1]);
		free(std_inout);
		exit_error("Error in dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(std_inout[1], STDOUT_FILENO) == -1)
	{
		close(std_inout[0]);
		close(std_inout[1]);
		free(std_inout);
		exit_error("Error in dup2");
		exit(EXIT_FAILURE);
	}
	close(std_inout[0]);
	close(std_inout[1]);
	free(std_inout);
}

bool	is_built_in(t_parser *commands, t_data *data)
{
	int	*stdinout;

	if (commands->args == NULL)
		return (false);
	stdinout = redir_builtin(commands);
	if (ft_strncmp(commands->args[0], "jp", 3) == 0)
		return (exec_jp(commands, stdinout));
	if (ft_strncmp(commands->args[0], "exit", 5) == 0)
		return (exec_exit(commands, stdinout));
	else if (ft_strncmp(commands->args[0], "cd", 3) == 0)
		return (exec_cd(commands, data, stdinout));
	else if (ft_strncmp(commands->args[0], "pwd", 4) == 0)
		return (exec_pwd(commands, stdinout));
	else if (ft_strncmp(commands->args[0], "echo", 5) == 0)
		return (exec_echo(commands, stdinout));
	else if (ft_strncmp(commands->args[0], "env", 4) == 0)
		return (exec_env(commands, data, stdinout));
	else if (ft_strncmp(commands->args[0], "unset", 6) == 0)
		return (exec_unset(commands, data, stdinout));
	else if (ft_strncmp(commands->args[0], "export", 7) == 0)
		return (exec_export(commands, data, stdinout));
	return (unset_std(stdinout), false);
}
