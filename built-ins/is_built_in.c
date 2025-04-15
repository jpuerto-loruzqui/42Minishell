/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/15 11:26:36 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_redir_builtin(t_parser *commands)
{
	int	fd_in;

	if (commands->here_fd)
	{
		if (commands->here_fd < 0)
			perror("here_fd");
		if (dup2(commands->here_fd, STDIN_FILENO) == -1)
			perror("dup2 heredoc:");
		close(commands->here_fd);
		return ;
	}
	if (commands->infile)
	{
		fd_in = open(commands->infile, O_RDONLY);
		if (fd_in < 0)
			perror("");
		else if (dup2(fd_in, STDIN_FILENO) == -1)
			perror("input_redir:");
		close(fd_in);
	}
}

int	*redir_builtin(t_parser *commands)
{
	int	*std_inout;

	std_inout = malloc(sizeof(int) * 2);
	if (!std_inout)
		return (NULL);
	std_inout[0] = dup(STDIN_FILENO);
	std_inout[1] = dup(STDOUT_FILENO);
	if (commands->infile)
		input_redir_builtin(commands);
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

	stdinout = 0;
	if (commands->args == NULL)
		return (false);
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
	return (false);
}
