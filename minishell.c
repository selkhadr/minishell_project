/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:15:15 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/23 14:53:48 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_struct	g_glo;

int	main(int ac, char **av, char **envp)
{
	t_token	*all;
	// t_env	*env;
	t_all	*globy;

	all = NULL;
	globy = NULL;
	g_glo.exitstatus = 0;
	// take_env(envp);
	prompt(&all, &globy, envp);
	// deallocating_env(&env);
	// system("leaks minishell");
	(void)ac;
	(void)av;
}
