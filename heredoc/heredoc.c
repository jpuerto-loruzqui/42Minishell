/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:42:14 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 18:53:16 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_heredoc_delimiter(t_lexer *tokens)
{
	t_lexer	*tok;

	if (!tokens || !tokens->data)
		return (NULL);
	tok = tokens;
	while (tok)
	{
		if (tok->data && ft_strncmp(tok->data, "<<", 2) == 0)
		{
			if (tok->next)
				return (tok->next->data);
			else
				return (NULL);
		}
		tok = tok->next;
	}
	return (NULL);
}

#include <string.h>
#include <unistd.h>

void	print_prompt(void)
{
	write(STDOUT_FILENO, COLOR_USERS, strlen(COLOR_USERS));
	write(STDOUT_FILENO, "heredoc> ", strlen("heredoc> "));
	write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
}

int	ft_heredoc(char *delim)
{
	int		fd;
	char	*line;
	char	*temp_filename;

	temp_filename = "/tmp/.heredoc_temp";
	fd = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	unlink(temp_filename);
	while (1)
	{
		print_prompt();
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}
