/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:44:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 09:41:12 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_unused_pipes(int num_commands, int i, int ***array_pipes)
{
	int	j;

	j = 0;
	while (j < num_commands - 1)
	{
		if (j != i && j != i - 1)
		{
			close((*array_pipes)[j][0]);
			close((*array_pipes)[j][1]);
		}
		j++;
	}
}

void	ft_close_all_pipes(t_data *data, int **array_pipes)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close(array_pipes[i][0]);
		close(array_pipes[i][1]);
		i++;
	}
}
