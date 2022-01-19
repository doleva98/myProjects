#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void UsrHandlerParent(int sig);
void UsrHandlerChild(int sig);

static pid_t pid2;

int main()
{
	struct sigaction parent_action, child_action;

	parent_action.sa_handler = UsrHandlerParent;
	parent_action.sa_flags = 0;
	sigemptyset(&parent_action.sa_mask);

	child_action.sa_handler = UsrHandlerChild;
	child_action.sa_flags = 0;
	sigemptyset(&child_action.sa_mask);

	sigaction(SIGUSR2, &parent_action, NULL);
	sigaction(SIGUSR1, &child_action, NULL);
	pid2 = fork();

	if (0 < pid2)
	{
		/* parent process */
		kill(pid2, SIGUSR1);
		wait(NULL);
	}
	while (1)
		;

	return 0;
}

void UsrHandlerParent(int sig)
{
	puts("pong");
	kill(pid2, SIGUSR1);
}

void UsrHandlerChild(int sig)
{
	puts("ping");
	kill(getppid(), SIGUSR2);
}
