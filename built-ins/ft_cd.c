/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:50:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/26 15:50:37 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **args)
{
	if (!args[1] || args[2])
	{
		printf("cd: usage: cd <path>\n");
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
