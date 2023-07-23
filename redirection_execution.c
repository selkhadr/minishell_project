/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:04:18 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 18:17:24 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_all *all)
{
	if (all->prev_pip != 0)
		close(all->prev_pip);
	if (all->next)
		close(all->pip[1]);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free (ptr[i++]);
	free (ptr);
}

void	use_execve(t_all *all, char **env)
{
	if (!all || !all->path || !all->cmds)
		exit (0) ;
	execve(all->path, all->cmds, env);
	perror ("execve");
	exit (g_glo.exitstatus);
}

void	close_heredoc(t_all *all)
{
	t_all	*tmp;

	tmp = all;
	while (tmp)
	{
		if (check_redirct(tmp, HEREDOC))
			close(tmp->fd);
		tmp = tmp->next;
	}
}
