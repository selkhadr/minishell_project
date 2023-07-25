/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:28:30 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/24 20:59:35 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_token **all, t_all **glo, char **envp)
{
	signal (SIGINT, handler_fnct);
	signal (SIGQUIT, SIG_IGN);
	g_glo.old_exitstatus = 7;
	while (1)
	{
		g_glo.line = readline("minishell> ");
		if (g_glo.line == NULL)
		{
			printf("exit\n");
			return ;
		}
		if (g_glo.line[0] != '\0' && g_glo.line[0] != '\n')
		{
			add_history(g_glo.line);
			g_glo.expanded = change_the_line(g_glo.line);
			if (found_error_one(all) || !g_glo.expanded)
				continue ;
			parsing_part_one(all, g_glo.expanded);
			if (found_error_two(all))
				continue ;
			parsing_part_two(all, glo);
			execution_fnct(*glo, envp);
			deallocating1(glo);
		}
		error_message(0, all);
	}
}
