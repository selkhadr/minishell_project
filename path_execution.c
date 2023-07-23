/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:00:29 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 15:13:59 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*path_with_slash(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		fd_printf(2, "minishell: %s: No such file or directory\n", cmd);
		exit (1);
	}
	return (cmd);
}

void	check_path(t_all *all)
{
	if (!all || !all->cmds || !all->cmds[0])
		return ;
	if (check_empty_cmd(all->cmds[0]))
	{
		fd_printf(2, "minishell: %s: command not found\n", all->cmds[0]);
		exit (127);
	}
	if (ft_strchr(all->cmds[0], '/'))
		all->path = path_with_slash(all->cmds[0]);
	else
	{
		all->path = normal_path(all->cmds[0], expanded_value("PATH"));
		if (!all->path)
		{
			fd_printf(2, "minishell: %s: command not found\n", all->cmds[0]);
			exit (127);
		}
	}
}

char	**normal_path_sequel(char *str, char *path)
{
	int		i;
	char	**paths;

	i = 0;
	if (!path)
	{
		// printf("%s\n", path);
		fd_printf(2, "minishell: %s: No such file or directory\n", str);
		exit (1);
	}
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char	*normal_path(char *cmd, char *path)
{
	int		i;
	char	**paths;
	char	*valid_cmd;

	paths = normal_path_sequel(cmd, path);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], cmd);
		if (access(paths[i], F_OK) == 0)
		{
			valid_cmd = ft_strdup(paths[i]);
			free_double_ptr(paths);
			return (valid_cmd);
		}
		i++;
	}
	free_double_ptr(paths);
	return (NULL);
}
