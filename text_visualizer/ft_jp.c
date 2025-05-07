/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:02 by jpuerto           #+#    #+#             */
/*   Updated: 2025/05/07 11:36:23 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_clear_and_welcome(char *file)
{
	printf("\033[2J\033[H");
	printf("\033[96m        __  ____  ____  ____  _  _  ____  \n\033[0m");
	printf("\033[96m      _(  )(  _ \\(_  _)(  __)( \\/ )(_  _) \n\033[0m");
	printf("\033[96m     / \\) \\ ) __/  )(   ) _)  )  (   )(  \n\033[0m");
	printf("\033[96m     \\____/(__)   (__) (____)(_/\\_) (__) \n\033[0m");
	printf("		  By jpuerto- & loruzqui\n");
	printf("\033[96m\n--- Welcome to Jp Text Visualizer!");
	printf(", reading: \"%s\"   ---\n\n\033[0m", file);
}

static void	ft_show_file(char *file, int fd, char *line)
{
	int		line_count;
	char	key;
	int		i;

	i = 0;
	while (line != NULL)
	{
		ft_clear_and_welcome(file);
		line_count = 0;
		while (line_count++ < 20 && line != NULL)
		{
			line = get_next_line(fd);
			printf("\033[93m - %i :\033[0m   %s", i++, line);
			free(line);
		}
		printf("\n\033[93m\n- Press ENTER to continue 'q' to quit -\033[0m\n");
		while (1)
		{
			key = ft_read_key();
			if (key == 'q')
				return ;
			else if (key == '\n')
				break ;
		}
	}
}

static char	*ft_get_file(void)
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

void	ft_show_visualizer(char *file)
{
	int		fd;
	int		flag;
	char	*line;

	line = "";
	if (!file)
	{
		file = ft_get_file();
		flag = 1;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Jp visualizer: Error opening file\n", 2));
	write(1, "\033[?1049h", 8);
	signal(SIGINT, ft_sigint_visualizer);
	ft_set_raw_mode(STDIN_FILENO);
	ft_show_file(file, fd, line);
	write(1, "\033[?1049l", 8);
	ft_restore_terminal(STDIN_FILENO);
	signal(SIGINT, ft_sigint_handler);
	if (flag == 1)
		free(file);
	close(fd);
}
