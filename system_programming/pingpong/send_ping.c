#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

static pid_t pid2;

void UsrHandlerParent(int signum, siginfo_t *siginfo, void *context);

int main()
{
	struct sigaction parent_action;
	puts("send ping to");

	scanf("%d", &pid2);
	parent_action.sa_sigaction = UsrHandlerParent;
	parent_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &parent_action, NULL);
	kill(pid2, SIGUSR1);
	while (1)
		;
	return 0;
}

void UsrHandlerParent(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)context;
	puts("pong");
	kill(siginfo->si_pid, SIGUSR1);
}