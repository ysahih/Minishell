/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:40:22 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 17:40:47 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	invalid_unset(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (!((c[i] >= 65 && c[i] <= 90) || (c[i] >= 97 && c[i] <= 122) || \
		(c[i] >= 48 && c[i] <= 57) \
		|| (c[i] == '_')))
			return (1);
		i++;
	}
	return (0);
}