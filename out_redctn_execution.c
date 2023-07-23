/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redctn_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:38:04 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/22 13:55:32 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_redirect(t_all *all)
{
	t_all	*tmp;

	tmp = all;
	if (check_redirct(tmp, REDIR_OUT) || check_redirct(tmp, APPEND))
		dup_last_out(tmp, creat_outfile(tmp));
	else if (tmp->next)
		dup2(tmp->pip[WRIT], STDOUT_FILENO);
}

void	dup_last_out(t_all *tmp, int n)
{
	int	fd;
	DIR	*dir;

	if (tmp->file_types[n] == REDIR_OUT)
	{
		fd = open (tmp->file_names[n], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit (1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else if (tmp->file_types[n] == APPEND)
	{
		fd = open (tmp->file_names[n], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			exit (1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
}

void	creat_outfile_sequel(t_all *all, int *last, int i)
{
	int	fd;
	DIR	*dir;

	if (all->file_types[i] == REDIR_OUT)
	{
		dir = opendir(all->file_names[i]);
		if (dir != NULL)
		{
        	print_error(all->file_names[i], ": Is a directory\n", 1);
    		closedir(dir);
			exit (1);
		}
		fd = open(all->file_names[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit (1);
		close (fd);
		*last = i;
	}
	else if (all->file_types[i] == APPEND)
	{
		dir = opendir(all->file_names[i]);
		if (dir != NULL)
		{
        	print_error(all->file_names[i], ": Is a directory\n", 1);
    		closedir(dir);
			exit (1);
		}
		fd = open(all->file_names[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit (1);
		close (fd);
		*last = i;
	}
}

int	creat_outfile(t_all *all)
{
	int	i;
	int	last;

	i = 0;
	while (all->file_names[i])
	{
		if (all->file_types[i] == REDIR_IN)
		{
			if (access(all->file_names[i], F_OK) == -1)
			{
				fd_printf(2, "minishell: %s: No such file or directory\n", all->file_names[i]);
				exit (1);
			}
		}
		creat_outfile_sequel(all, &last, i);
		i++;
	}
	return (last);
}

void	print_error(char *str, char *s2, int flag)
{
	if (flag)
		fd_printf(2, "minishell: ");
	if (str == NULL)
		fd_printf(2, s2, ft_strlen(s2));
	else
	{
		fd_printf(2, str, ft_strlen(str));
		fd_printf(2, s2, ft_strlen(s2));
	}
}
