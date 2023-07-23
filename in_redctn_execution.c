/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redctn_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:56:41 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/22 13:29:43 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirct(t_all *tmp, int flag)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp->file_names && tmp->file_names[i])
	{
		if (tmp->file_types[i] == flag)
			return (1);
		i++;
	}
	return (0);
}

int	last_input(t_all *tmp)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (tmp->file_names[i])
	{
		if (tmp->file_types[i] == REDIR_IN || tmp->file_types[i] == HEREDOC)
			last = i;
		if (tmp->file_types[i] == REDIR_IN)
		{
			if (access(tmp->file_names[i], F_OK) == -1)
			{
				fd_printf(2, "minishell: %s: No such file or directory\n", tmp->file_names[i]);
				exit (1);
			}
		}
		i++;
	}
	return (last);
}

void	in_redirect(t_all *all)
{
	t_all	*tmp;
	int		fd;
	int		last_in;
	DIR		*dir;

	tmp = all;
	if (check_redirct(tmp, REDIR_IN) || check_redirct(tmp, HEREDOC))
	{
		last_in = last_input(tmp);
		if (tmp->file_types[last_in] == REDIR_IN)
		{
			dir = opendir(tmp->file_names[last_in]);
			if (dir != NULL)
			{
            	fd_printf(2, "cat: stdin: Is a directory\n");
        		closedir(dir);
				exit (1);
			}
			fd = open(tmp->file_names[last_in], O_RDWR, 0644);
			if (fd == -1)
				exit (1);
			dup2(fd, STDIN_FILENO);
			close (fd);
		}
		else
		{
			dup2(tmp->fd, STDIN_FILENO);
			close (tmp->fd);
		}
	}
	else if (tmp->prev_pip != 0)
		dup2(tmp->prev_pip, STDIN_FILENO);
}
