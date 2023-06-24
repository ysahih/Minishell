/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:03:37 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/24 11:21:53 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *st1, char *st2, size_t n)
{
	size_t			i;

	i = 0;

	if (st1 == NULL)
	{
		return (-1);
	}
	else if (st2 == NULL)
	{
		return (1);
	}
	while ((st1[i] != '\0' || st2[i] != '\0') && i < n)
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}
