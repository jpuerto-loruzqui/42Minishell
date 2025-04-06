/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:08:10 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 19:08:11 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strdup_matrix(char **matrix)
{
	int		size;
	char	**new_matrix;
	int		i;

	size = 0;
	if (!matrix)
		return (NULL);
	while (matrix[size])
		size++;
	new_matrix = malloc(sizeof(char *) * (size + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		if (!new_matrix[i])
			ft_free_split(new_matrix);
		i++;
	}
	new_matrix[size] = NULL;
	return (new_matrix);
}
