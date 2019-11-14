#include "sh.h"
#include <signal.h>
#include <stdio.h>
static int received = 0;

void sig_handler(int signo);




int main( int argc, char **argv, char **envp )
{
  /* put signal set up stuff here */
		signal(SIGINT, sig_handler);
		signal(SIGTSTP, sig_handler);



  return sh(argc, argv, envp);
}

void sig_handler(int signo)
{
  /* define your signal handler */
	if(signo == SIGINT)
		received = 1;
	else if(signo == SIGTSTP)
		received = 1;
	printf("\nCaught signal %d\n", signo);
	fflush(stdout);
}

