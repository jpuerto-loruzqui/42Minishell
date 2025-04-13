/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:02 by jpuerto           #+#    #+#             */
/*   Updated: 2025/04/13 14:11:57 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_and_welcome(char *file)
{
	printf("\033[2J\033[H");
	printf("\033[96m        __  ____  ____  ____  _  _  ____  \n\033[0m");
	printf("\033[96m      _(  )(  _ \\(_  _)(  __)( \\/ )(_  _) \n\033[0m");
	printf("\033[96m     / \\) \\ ) __/  )(   ) _)  )  (   )(  \n\033[0m");
	printf("\033[96m     \\____/(__)   (__) (____)(_/\\_) (__) \n\033[0m");
	printf("		  By jpuerto- & loruzqui\n");
	printf("\033[96m\n--- Welcome to Jp Text Visualizer!");
	printf(", reassding: \"%s\"   ---\n\n\033[0m", file);
}

void	show_file(char *file, int fd, char *line)
{
	int		line_count;
	char	key;
	int		i;

	i = 0;
	while (line != NULL)
	{
		clear_and_welcome(file);
		line_count = 0;
		while (line_count++ < 20 && (line = get_next_line(fd)) != NULL)
		{
			printf("\033[93m - %i :\033[0m   %s", i++, line);
			free(line);
		}
		printf("\n\033[93m-- Press ENTER to continue, 'q' to quit --\033[0m\n");
		while (1)
		{
			key = read_key();
			if (key == 'q')
				return ;
			else if (key == '\n')
				break ;
		}
	}
}

char	*get_file(void)
{
	char	*input;
	char	*newline_pos;

	ft_putstr_fd("Jp visualizer: write file name\n", 1);
	input = get_next_line(STDIN_FILENO);
	if (!input)
	{
		ft_putstr_fd("Error reading input\n", 2);
		return (NULL);
	}
	newline_pos = ft_strchr(input, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	return (input);
}

void	show_visualizer(char *file)
{
	int		fd;
	int		flag;
	char	*line;

	line = "";
	if (!file)
	{
		file = get_file();
		flag = 1;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Jp visualizer: Error opening file\n", 2));
	write(1, "\033[?1049h", 8);
	signal(SIGINT, sigint_visualizer);
	set_raw_mode(STDIN_FILENO);
	show_file(file, fd, line);
	write(1, "\033[?1049l", 8);
	restore_terminal(STDIN_FILENO);
	signal(SIGINT, sigint_handler);
	if (flag == 1)
		free(file);
	close(fd);
}
