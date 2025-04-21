/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:55:35 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/21 07:38:43 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	if (s1 && s1[0])
		free(s1);
	if (s2 && s2[0])
		free(s2);
	return (str);
}
