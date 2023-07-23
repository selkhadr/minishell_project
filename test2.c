/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:14:06 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/22 12:17:01 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    struct stat fileStat;

    const char *path = "example_directory"; // Replace with the name you want to check
    if (access(path, F_OK) == 0)
	{
        if (lstat(path, &fileStat) == 0)
		{
            if (S_ISDIR(fileStat.st_mode)) {
                printf("%s is a directory.\n", path);
            } else {
                printf("%s is a file.\n", path);
            }
        }
		else
            perror("Error while accessing file/directory information");
    }
	else
        perror("File/directory not found");
    return 0;
}
