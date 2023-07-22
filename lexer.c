#include "minishell.h"

void	tokenize_word(t_lexer **node, char **s)
{
	int	i;

	char *tmp;

	tmp = *s;
	i = 0;
	
	while (tmp[i] && !is_symbol(tmp[i]))
	{
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
			break ;
		i++;
	}
	create_node(node, ft_strcpy(*s, i), WORD, 0);
	*s += i;
}

void	tokenize_var(t_lexer **node, char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	*s += 1;
	tmp = *s;
	if (tmp[0] == '?')
	{
		create_node(node, "?", VAR, 0);
		*s += 1;
		return ;
	}
	if (!tmp[i] || !valid_var(tmp[i]))
		return ;
	while(tmp[i] && valid_var(tmp[i]))
		i++;
	create_node(node, ft_strcpy(tmp, i), VAR, 0);
	*s += i;
}

void	tokenize_dquote(t_lexer **node, char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	*s += 1;
	tmp = *s;
	create_node(node, "\"", DQUOTE, 0);
	while (tmp[i])
	{
		if (tmp[i] == '"')
		{
			create_node(node, "\"", DQUOTE, 0);
			*s = &tmp[++i];
			return ;
		}
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
		{
			j = ++i;
			while (tmp[i] && valid_var(tmp[i]))
				i++;
			create_node(node, ft_strcpy(tmp + j, i - j), VAR, 0);
			*s = &tmp[i];
		}
		else
		{
			j = i;
			while (tmp[i] && tmp[i] != '"')
			{
				if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
					break ;
				i++;
			}
			create_node(node, ft_strcpy(tmp + j, i - j), WORD, 0);
			*s = &tmp[i];
		}
	}
}

void	tokenize_squote(t_lexer **node, char **s)
{
	char	*tmp;
	int		i;

	i = 0;
	*s += 1;
	tmp = *s;
	create_node(node, "'", SQUOTE, 0);
	while (tmp[i] && tmp[i] != '\'')
		i++;
	if (i)
		create_node(node, ft_strcpy(tmp, i), WORD, 0);
	if (tmp[i] == '\'')
	{
		create_node(node, "'", SQUOTE, 0);
		i++;
	}
	// printf("|%c|\n", tmp[i - 1]);
	*s += i;
}

void	tokenize_red(t_lexer **node, char **s)
{
	char *line;

	line = *s;
	if (*line == '>')
	{
		if (*(line + 1) && *(line + 1) == '>')
		{
			create_node(node, ">>", APPEND, 0);
			line++;
		}
		else
			create_node(node, ">", OUTRED, 0);
		line++;
	}
	else if (*line == '<')
	{
		if (*(line + 1) && *(line + 1) == '<')
		{
			create_node(node, "<<", HERDOC, 0);
			line++;
		}
		else
			create_node(node, "<", INRED, 0);
		line++;
	}
	*s = line;
}

void	get_token(t_lexer **node, char **line, int type)
{
	if (type == PIPE)
	{
		create_node(node, "|", PIPE, 0);
		(*line)++;
	}
	if (type == WSPACE)
	{
		create_node(node, " ", WSPACE, 0);
		while (**line == ' ')
			(*line)++;
	}
	if (type == -1)
	{
		create_node(node, "*", -1, 0);
		(*line)++;
	}
}

t_lexer	*tokenize(char *line)
{
	t_lexer *node;
	char 	*tmp;

	tmp = line;
	node = NULL;
	while(*line == ' ')
		line++;
	while (*line)
	{
		if (*line == ' ')
			get_token(&node, &line, WSPACE);
		else if (*line == '|')
			get_token(&node, &line, PIPE);
		else if (*line == '"')
			tokenize_dquote(&node, &line);
		else if (*line == '\'')
			tokenize_squote(&node, &line);
		else if (*line == '*')
			get_token(&node, &line, -1);
		else if (*line == '>'|| *line == '<')
			tokenize_red(&node, &line);
		else if (*line == '$' && *(line + 1) && (valid_var(*(line + 1)) || *(line + 1) == '?'))
			tokenize_var(&node, &line);
		else
			tokenize_word(&node, &line);
	}
	// t_lexer	 *tmp = node;
	// puts("ls");
	// while (tmp)
	// {
	// 	printf("|%s|-%d\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
	free(tmp);
	return (node);
}