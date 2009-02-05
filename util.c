/**
 * @name
 * @brief Malloc and other utilities all with error checking. 
 * @author Nathaniel "Nat" Welch
 * @version 0.42
 *
 * DF 82 8A F5 6F EF 0F 15 F6 12 09 0B 03 21 DA CF
 */

#include "util.h"

/**
 * Safe Malloc, from Smith's Lecture. Basically mallocing 
 * with error checking.
 * @param [in] numBytes Number of bits you want to allocate.
 * @return a void pointer to fresh allocated memory.
 */
void *smalloc(int numBytes)
{
	void *p = malloc(numBytes);
	if(p == NULL)
	{
		perror("malloc");
		exit(-1);
	}

	return p;
}

/**
 * Safe Realloc, from Smith's Lecture.
 * @param [in] p current pointer you want to reallocate 
 * memory to.
 * @param [in] numBytes Number of bits you want to allocate.
 * @return a void pointer to fresh allocated memory.
 */
void *srealloc(void *p, int numBytes)
{
	void *q = realloc(p,numBytes);
	if(q == NULL)
	{
		perror("realloc");
		exit(-1);
	}

	return q;
}

/**
 * sys call for writing from pipe in to pipe to.
 * from a handout by Hugh Smith. 
 * @param [in] in Pipe to read from.
 * @param [in] out pipe to write to.
 */
void cat(int in, int out)
{
	int num;
	char buffer[256];

	while((num = read(in,buffer,256)) > 0)
	{
		if(write(out,buffer,num) < 0)
		{
			perror("write");
			break;
		}
	}
	if(num < 0)
	{
		perror("read");
	}
}

/**
 * A safe version of fork, or rather an error handling one
 * @return 0 to child, pid of child to parent. 
 */
pid_t sfork(void)
{
	pid_t pid;

	if((pid = fork()) < 0)
	{
		perror("fork");
		exit(-1);
	}

	return pid;
}

/**
 * A safe version of pipe, eg, it handles errors and such.
 * fd[0] is set up for reading, fd[1] is set up for writing.
 * @param [out] pipefd int array size 2 you want to be a pipe.
 */
void spipe(int pipefd[2])
{
	if (pipe(pipefd) == -1) 
	{
		perror("pipe");
		exit(-1);
	}
	else
	{
		//fprintf(stderr,"-- Opened fd %d and %d.\n",pipefd[0],pipefd[1]);
	}
}

/**
 * Toggles the selected File Descriptor O_NONBLOCK option. 
 * Call by setblock(STDIN_FILENO, 0);
 * @param [in] fd File Descriptor
 * @param [in] block 1 to turn off, 0 to turn on
 * @return Returns 1 every time. 
 */
//TODO: Add Bug checking.
int setblock(int fd, int block)
{
	int flags;

	flags = fcntl(fd, F_GETFL);

	if(block)
	{
		flags &= ~O_NONBLOCK;
	}
	else
	{
		flags |= O_NONBLOCK;
	}

	fcntl(fd, F_SETFL, flags);

	return 1;
}

/**
 * It's like dup2, but with error checking!
 * @return see dup2(2)
 * @param [in] oldfd File descriptor you want 
 * to close and clone.
 * @param [in] newfd File descriptor you want 
 * to open with oldfd's content.
 */
int sdup2(int oldfd, int newfd)
{
	int ret = -1;

	if((ret = dup2(oldfd, newfd)) == -1)
	{
		perror("dup2");
		exit(-1);
	}

	return ret;
}

/**
 * This is like close but has an easy place to 
 * add error reporting. This does not add any special error checking atm.
 * @return returns zero on success. On error, -1 is returned
 * @param [in] fd File Descriptor to close.
 */
int sclose(int fd)
{
	//fprintf(stderr,"--- Closing fd %d.\n",fd);
	return close(fd);
}

/**
 * Disables Ctrl + C and Ctrl + Z for current program.
 */
void stopblock(void)
{
	// Ignore Ctrl+z and Ctrl+c (Insert maniacle laugh here...)
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN); 

	return;
}
		
/**
 * Enables Ctrl + C and Ctrl + Z for current program.
 */
void startblock(void)
{
	// Oh Noes, the man, he can stop us!
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, SIG_DFL); 

	return;
}
