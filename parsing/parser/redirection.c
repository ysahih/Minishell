#include"../../minishell.h"

void	read_hd( char *s, int fd[2])
{
	char	*line;

	while(true)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, s) == 0 || gl.rl)
		{
			gl.rl = 0;
			if (line)
				free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	free(s);
}

void	parse_hd(t_simple_cmd **scmd, t_lexer **cmdline)
{
	int		fd[2];
	char *s;

	if (pipe(fd) == -1)
	{
		(*scmd)->err = errno;
		return ;
	}
	rl_event_hook = event;
	signal(SIGINT, hd_sig);
	(*cmdline) = (*cmdline)->next;
	s = ft_strdup("");
	if ((*cmdline))
	{
		free(s);
		s = (*cmdline)->str;
	}
	read_hd( s, fd);
	if ((*cmdline))
		(*cmdline) = (*cmdline)->next;
	(*scmd)->in_fd = fd[0];
}

void	set_in_fd(t_simple_cmd **cmd, int new_fd)
{
	int	old_fd;

	old_fd = (*cmd)->in_fd;
	if (old_fd != 0)
		close(old_fd);
	(*cmd)->in_fd = new_fd;
		if((*cmd)->in_fd < 0)
			(*cmd)->err = errno;
}

void	set_out_fd(t_simple_cmd **cmd, int new_fd)
{
	int	old_fd;

	old_fd = (*cmd)->out_fd;
	if (old_fd != 1)
		close(old_fd);
	(*cmd)->out_fd = new_fd;
		if((*cmd)->out_fd < 0)
			(*cmd)->err = errno;
}

void	parse_red(t_lexer **cmdline, t_simple_cmd **cmd)
{
	int		flag;
	int		new_fd;

	flag = (*cmdline)->type;
	(*cmdline) = (*cmdline)->next;
	if (flag == OUTRED)
	{
		new_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		set_out_fd(cmd, new_fd);
	}
	else if (flag == INRED)
	{
		new_fd = open((*cmdline)->str, O_RDONLY, 0644);
		set_in_fd(cmd, new_fd);
	}
	else if (flag == APPEND)
	{
		new_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		set_out_fd(cmd, new_fd);
	}
	free((*cmdline)->str);
	(*cmdline) = (*cmdline)->next;
}
