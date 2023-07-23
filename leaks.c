#include <stdio.h>
#include <unistd.h>

int main()
{
	while (1)
	{
		system("leaks minishell");
		sleep(1);
	}
}
