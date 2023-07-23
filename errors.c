/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:39:08 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/21 17:54:39 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_error_one(t_token **all)
{
	if (closed_double_quotes(g_glo.line) || !g_glo.expanded)
	{
		error_message(1, all);
		// system("leaks minishell | tail -2");
		return (1);
	}
	if (g_glo.expanded[0] == '\0' || empty(g_glo.expanded) /*|| empty_and_not_empty()*/)
	{
		error_message(0, all);
		// system("leaks minishell | tail -2");
		return (1);
	}
	return (0);
}

int	found_error_two(t_token **all)
{
	if (syntax_error_first(all))
	{
		error_message(1, all);
		// system("leaks minishell | tail -2");
		return (1);
	}
	return (0);
}

void	error_message(int err, t_token **all)
{
	if (err == 1)
	{
		printf("Syntax error\n");
		g_glo.exitstatus = 1;
	}
	free(g_glo.line);
	g_glo.line = NULL;
	free(g_glo.expanded);
	g_glo.expanded = NULL;
	deallocating(all);
	// system("leaks minishell | tail -2");
}

int	empty_and_not_empty(void)
{
	int	i;

	if (g_glo.expanded[0] != 31)
		return (0);
	i = 0;
	g_glo.tmp = single_double_quotes(g_glo.expanded, 31, &i);
	g_glo.before = mer_substr(g_glo.tmp, 1, ft_strlen(g_glo.tmp) - 2);
	if (empty(g_glo.before))
	{
		printf("empty as shit\n");
		return (1);
	}
	return (0);
}