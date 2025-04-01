/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:02:45 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/26 16:02:47 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args)
{
	char	*cwd;

	if (args[1])
	{
		printf("pwd: usage: pwd\n");
		return (1);
	}
	cwd = getcwd(NULL, 0); //getcwd obtiene el directorio
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
