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
#include <assert.h>

pid_t other_pid;
static int got_signal = 0;
static int is_watchdog = 0;
char *calling_func = NULL;

static void SigHandlerIsAlive(int signum, siginfo_t *siginfo, void *context);
static void *WDThreadFunction(void *arg);
static int SendSignalTask(const void *param);
static int ReceiveSignalTask(const void *param);

int KeepMeAlive(int argc, char **argv)
{
	struct sigaction signal_handler_is_alive;
	pthread_t WDThread;
	scheduler_t *scheduler = NULL;
	void *thread_ret_value = NULL;

	(void)argc;

	signal(SIGCHLD, SIG_IGN);

	signal_handler_is_alive.sa_sigaction = SigHandlerIsAlive;
	signal_handler_is_alive.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_handler_is_alive, NULL);

	if (argv[1])
	{
		calling_func = argv[1];
		other_pid = getppid();
		if (0 == strcmp(argv[0], "./watchdog.out"))
		{
			/* now in watchdog */
			is_watchdog = 1;
		}
	}
	else
	{
		/* i am the 247 and the first
		invoked from console */

		other_pid = fork();

		if (-1 == other_pid)
		{
			return 1;
		}

		else if (0 == other_pid)
		{
			execlp("./watchdog.out", "./watchdog.out", argv[0], NULL);
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
	pthread_join(WDThread, &thread_ret_value);
	if (!thread_ret_value)
	{
		return 1;
	}

	return 0;
}

static void *WDThreadFunction(void *arg)
{
	unique_id_t uid = uid_null_uid;
	scheduler_t *scheduler = NULL;

	assert(arg);

	scheduler = (scheduler_t *)arg;

	uid = SchedulerTaskAdd(scheduler, SendSignalTask, 1, NULL);
	if (UIDIsEqual(uid, uid_null_uid))
	{
		return NULL;
	}

	uid = SchedulerTaskAdd(scheduler, ReceiveSignalTask, 3, NULL);
	if (UIDIsEqual(uid, uid_null_uid))
	{
		return NULL;
	}

	SchedulerRun(scheduler);

	return scheduler;
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
	}
	else
	{
		/* TODO: ressurection */
		other_pid = fork();
		if (-1 == other_pid)
		{
			return 1;
		}
		else if (0 == other_pid)
		{
			if (is_watchdog)
			{
				puts("");
				execlp(calling_func, calling_func, "./watchdog.out", NULL);
			}
			else
			{
				puts("");
				execlp("./watchdog.out", "./watchdog.out", calling_func, NULL);
			}
		}
		else
		{
			/* 			kill(other_pid, SIGUSR1);
			 */
/* 			wait(NULL);
 */		}
	}
	got_signal = 0;

	return 0;
}
