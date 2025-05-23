/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:00:29 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/24 20:09:27 by selkhadr         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit (126);
	}
	return (cmd);
}

void	check_path(t_all *all)
{
	char	*tmp;

	if (!all || !all->cmds || !all->cmds[0])
		return ;
	if (check_empty_cmd(all->cmds[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(all->cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	if (ft_strchr(all->cmds[0], '/'))
		all->path = path_with_slash(all->cmds[0]);
	else
	{
		tmp = expanded_value("PATH");
		all->path = normal_path(all->cmds[0], tmp);
		if (!all->path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(all->cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
	free (path);
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
