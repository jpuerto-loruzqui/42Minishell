/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/12 12:58:34 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*redir_builtin(t_parser *commands)
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
	if (ft_strncmp(commands->args[0], "exit", 5) == 0)
		return (ft_exit(commands), unset_std(stdinout), true);
	else if (ft_strncmp(commands->args[0], "cd", 3) == 0)
		return (ft_cd(commands->args, data), unset_std(stdinout), true);
	else if (ft_strncmp(commands->args[0], "pwd", 4) == 0)
		return (ft_pwd(commands->args), unset_std(stdinout), true);
	else if (ft_strncmp(commands->args[0], "echo", 5) == 0)
		return (ft_echo(commands->args), unset_std(stdinout), true);
	else if (ft_strncmp(commands->args[0], "env", 4) == 0)
		return (ft_env(commands->args, data->env), unset_std(stdinout), true);
	else if (ft_strncmp(commands->args[0], "unset", 6) == 0)
	{
		ft_unset(commands->args, data->env);
		ft_free_split(data->env_arr);
		data->env_arr = ft_lsttoa(*data);
		return (unset_std(stdinout), true);
	}
	else if (ft_strncmp(commands->args[0], "export", 7) == 0)
	{
		ft_export(commands->args, data);
		ft_free_split(data->env_arr);
		data->env_arr = ft_lsttoa(*data);
		return (unset_std(stdinout), true);
	}
	return (unset_std(stdinout), false);
}
