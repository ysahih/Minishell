/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:41:06 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/20 18:41:41 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long	ft_atoi(char *str)
{
	int					i;
	int					s;
	unsigned long long	n;

	s = 1;
	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(s *= -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + str[i++] - 48;
	if (((str[i] < 48 || str[i] > 57) && str[i]) || n * s > 9223372036854775807)
	{
		printf("exit\nsash: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (n * s);
}

int	ex_it(t_all *all)
{
	t_simple_cmd	*p;
	int				nbr;

	p = all->cmd;
	if (!p->str[1])
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_atoi(p->str[1]) && p->str[2])
	{
		printf("exit\nsash: exit: too many arguments\n");
		exit(1);
	}
	nbr = ft_atoi(p->str[1]);
	if (!p->str[2] && p->str[1])
	{
		printf("exit\n");
		exit(nbr);
	}
	return (0);
}
