#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "watchdog_lib.h"
#include "scheduler.h"
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include <pthread.h>
#include <sys/types.h>/* for fork */
#include <unistd.h>	  /* for fork */
#include <sys/wait.h>
#include <string.h>

pid_t other_pid;
static int got_signal = 0;
static int is_watchdog = 0;

static void SigHandlerIsAlive(int signum, siginfo_t *siginfo, void *context);
static void *WDThreadFunction(void *arg);
static int SendSignalTask(const void *param);
static int ReceiveSignalTask(const void *param);

int KeepMeAlive(int argc, char **argv)
{
	struct sigaction signal_handler_is_alive;
	pthread_t WDThread;
	scheduler_t *scheduler = NULL;

	/* 	char *env_var = getenv("env_var_watchdog");
	 */
	(void)argc;
	signal_handler_is_alive.sa_sigaction = SigHandlerIsAlive;
	signal_handler_is_alive.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_handler_is_alive, NULL);
	/* sem_t *sema;
	int counter = 0; */

	/* 	sema = sem_open(argv[1], O_CREAT, 0666, counter); */

	if (strcmp(argv[0], "./watchdog.out") == 0)
	{
		/* now in watchdog */
		is_watchdog = 1;
		other_pid = getppid();
	}

	else
	{
		/* i am the 247 and invoked from console */
		/* 		setenv("env_var_watchdog", "watchdog", 0);
		 */
		other_pid = fork();

		if (-1 == other_pid)
		{
			return 1;
		}

		else if (0 == other_pid)
		{
			execlp("./watchdog.out", "./watchdog.out", NULL);
		}
	}

	scheduler = SchedulerCreate();
	if (!scheduler)
	{
		return 1;
	}

	if (0 != pthread_create(&WDThread, NULL, WDThreadFunction, scheduler))
	{
		return 1;
	}
	return 0;
}

static void *WDThreadFunction(void *arg)
{

	scheduler_t *scheduler = (scheduler_t *)arg;

	SchedulerTaskAdd(scheduler, SendSignalTask, 3, NULL);
	SchedulerTaskAdd(scheduler, ReceiveSignalTask, 3, NULL);

	SchedulerRun(scheduler);

	return NULL;
}

static void SigHandlerIsAlive(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	(void)signum;

	got_signal = 1;
}

static int SendSignalTask(const void *param)
{
	(void)param;
	kill(other_pid, SIGUSR1);
	return 0;
}

static int ReceiveSignalTask(const void *param)
{
	(void)param;

	if (got_signal)
	{
		if (is_watchdog)
		{
			puts("watchdog got signal");
		}
		else
		{
			puts("247 got signal");
		}
		got_signal = 0;
	}
	else
	{
		/* TODO: ressurection */
	}
	return 0;
}
