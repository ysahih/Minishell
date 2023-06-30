/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/30 19:51:49 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd(t_all *all)
{
	t_simple_cmd	*tmp;

	tmp = all->cmd;
	if (!tmp->next)
	{
		if (!ft_strcmp(tmp->str[0], "env"))
			env(all);
		else if (!ft_strcmp(tmp->str[0], "export"))
			export(all);
		else if (!ft_strcmp(tmp->str[0], "pwd"))
			pwd(all);
		else if (!ft_strcmp(tmp->str[0], "echo"))
			echo(tmp);
		else if (!ft_strcmp(tmp->str[0] , "unset"))
			unset(tmp, &all->env, &all->exp);
		else if (!ft_strcmp(tmp->str[0], "exit"))
			ex_it (all);
		else if (!ft_strcmp(tmp->str[0], "cd"))
			cd (all);
		else
			one_cmd_nb(all, tmp);
	}
}

// void	many_cmds(t_all	*all)
// {
// 	t_simple_cmd	*tmp;

// 	tmp = all->cmd;
// 	while (tmp)
// 	{
		
// 	}
// }

int	exec(t_all *all)
{
	int i;
	t_simple_cmd *tmp;
	
	i = 0;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
		return (0);
	if (!tmp->next)
		one_cmd(all);
	// else
	// 	many_cmds(all);
	return (0);
}
