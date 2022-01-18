#define _POSIX_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

static void foo();
void UsrHandler(int sig);

static int received = 0;

int main()
{
	foo();
	return 0;
}

void UsrHandler(int sig)
{
	if (sig == SIGUSR1)
	{
		printf("ping");
		received = 1;
	}

	if (sig == SIGUSR2)
	{
		printf(" pong");
	}
}

static void foo()
{
	pid_t parent_pid = getpid();
	pid_t pid2;
	pid2 = fork();

	signal(SIGUSR1, UsrHandler);

	signal(SIGUSR2, UsrHandler);

	if (0 > pid2)
	{
		printf("Can't create child process\n");
	}
	else if (0 == pid2)
	{
		/* child process */
		kill(parent_pid, SIGUSR2);
	}
	else
	{
		/* parent process */
		kill(pid2, SIGUSR1);

		wait(NULL);
	}
}