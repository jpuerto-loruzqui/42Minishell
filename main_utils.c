/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:24:09 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/20 14:24:31 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_control_getcwd(t_data *data)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: getcwd");
		tmp = ft_getenv("OLDPWD", data->env_arr);
		if (tmp)
			cwd = ft_strdup(tmp);
		else
			cwd = ft_strdup("~");
	}
	return (cwd);
}
