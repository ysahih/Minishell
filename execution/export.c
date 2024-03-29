/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:28:32 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/25 09:59:25 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	egal_not_exist(t_all *all, t_simple_cmd *p, int i)
{
	t_var	*tmp_ex;

	if (is_valid(p->str[i]) == -1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(p->str[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	tmp_ex = check_char(all->exp, p->str[i]);
	if (!tmp_ex)
		add_exen_back(&all->exp, lstnew_exen(ft_strdup(p->str[i]), NULL));
	all->exp = sort_env(all->exp);
}

void	check_egal(t_all *all, t_simple_cmd	*p, int i, int k)
{
	k = ft_strchr(p->str[i], '=');
	if (k != -1)
	{
		exist_egal(all, p, i, k);
	}
	else
	{	
		egal_not_exist(all, p, i);
	}
}

int	export(t_all *all, t_simple_cmd	*p)
{
	int				k;
	int				flag;
	int				i;

	k = 0;
	flag = 0;
	if (!p->str[1])
		only_exp(all, all->cmd->out_fd);
	else
	{
		i = 0;
		while (p->str[++i])
		{
			if (!valid_var(p->str[i][0]))
			{
				print_invalid(p, i);
				flag++;
			}
			else
				check_egal(all, p, i, k);
		}
	}
	if (flag != 0)
		return (1);
	return (0);
}
