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
	printf("%d\n", getpid());

	parent_action.sa_sigaction = UsrHandlerParent;
	parent_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &parent_action, NULL);
	while (1)
		;
	return 0;
}

void UsrHandlerParent(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)context;
	puts("ping");
	kill(siginfo->si_pid, SIGUSR2);
}