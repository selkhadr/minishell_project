#include <stdlib.h>
#include <unistd.h>

int main()
{
	while(1)
	{
		system("leaks minishell");
		sleep (1);
	}
	return (0);
}
