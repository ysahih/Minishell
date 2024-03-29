/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:35 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/23 17:39:44 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	analyze_syntax(t_lexer *cmd)
{
	if (!cmd)
		return (false);
	while (cmd)
	{
		if (cmd->type == WSPACE && cmd->next)
			cmd = cmd->next;
		if (cmd->type == PIPE)
			if (!pipe_analyze(cmd))
				return (false);
		if (cmd->type >= OUTRED && cmd->type <= HERDOC)
			if (!red_analyze(cmd))
				return (false);
		if (cmd->type == SQUOTE || cmd->type == DQUOTE)
		{
			if (cmd->type == SQUOTE)
				if (!analyze_quote(&cmd, SQUOTE))
					return (false);
			if (cmd->type == DQUOTE)
				if (!analyze_quote(&cmd, DQUOTE))
					return (false);
		}
		cmd = cmd->next;
	}
	return (true);
}
