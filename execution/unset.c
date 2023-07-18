/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:07:40 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/06 14:39:12 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone(t_var *lst)
{
	if (lst)
	{
		if (lst->key)
		{
			free(lst->key);
			lst->key = NULL;
		}
		if (lst->val)
		{
			free(lst->val);
			lst->val = NULL;
		}
		free(lst);
		lst = NULL;
	}
}

t_var	*check_exist_key(t_var	*lst, char	*str)
{
	if (!ft_strcmp(lst->key, str))
	{
		return (lst);
	}
	while (lst->next)
	{
		if (!ft_strcmp(lst->next->key, str))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_var	*unset_env(char *str, t_var **env)
{
	t_var	*exist_key_env;
	t_var	*tmp;

	exist_key_env = check_exist_key(*env, str);
	if (!exist_key_env)
		return (*env);
	if (exist_key_env == *env)
	{
		*env = (*env)->next;
		ft_lstdelone(exist_key_env);
	}
	else if (exist_key_env != NULL)
	{
		tmp = exist_key_env->next;
		exist_key_env->next = exist_key_env->next->next;
		ft_lstdelone(tmp);
	}
	return (*env);
}

t_var	*unset_exp(char *str, t_var **exp)
{
	t_var	*exist_key_exp;
	t_var	*tmp;

	exist_key_exp = check_exist_key(*exp, str);
	if (!exist_key_exp)
		return (*exp);
	if (exist_key_exp == *exp)
	{
		*exp = (*exp)->next;
		ft_lstdelone(exist_key_exp);
	}
	else if (exist_key_exp != NULL)
	{
		tmp = exist_key_exp->next;
		exist_key_exp->next = exist_key_exp->next->next;
		ft_lstdelone(tmp);
	}
	return (*exp);
}

void	unset(t_simple_cmd *p, t_var **env, t_var **exp)
{
	int	i;

	i = 1;
	while (p->str[i])
	{
		*env = unset_env(p->str[i], env);
		*exp = unset_exp(p->str[i], exp);
		i++;
	}
}
