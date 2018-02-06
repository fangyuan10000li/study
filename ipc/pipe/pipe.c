#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE		1024

int main()
{
	pid_t pid;
	int pd[2];
	char buf[BUFSIZE];

	if(pipe(pd) < 0)
	{
		perror("pipe");
		exit(1);
	}

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	if(pid == 0)	// child read
	{
		close(pd[1]);
		read(pd[0],buf,BUFSIZE);
		/*if error*/
		puts(buf);
		close(pd[0]);
		exit(0);
	}
	else			// parent write
	{
		close(pd[0]);
		write(pd[1],"Hello!",6);
		close(pd[1]);
		wait(NULL);
		exit(0);
	}

	exit(0);
}


