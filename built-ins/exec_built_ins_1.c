/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 21:53:35 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exec_jp(t_parser *cmd, int *stdinout)
{
	show_visualizer(cmd->args[1]);
	unset_std(stdinout);
	return (true);
}

bool	exec_exit(t_parser *cmd, int *stdinout)
{
	ft_exit(cmd);
	unset_std(stdinout);
	return (true);
}

bool	exec_cd(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_cd(cmd->args, data);
	unset_std(stdinout);
	return (true);
}

bool	exec_pwd(t_parser *cmd, int *stdinout)
{
	ft_pwd(cmd->args);
	unset_std(stdinout);
	return (true);
}

bool	exec_echo(t_parser *cmd, int *stdinout)
{
	ft_echo(cmd->args);
	unset_std(stdinout);
	return (true);
}
