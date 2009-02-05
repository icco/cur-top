/**
 * @name
 * @brief Nat Welch's Util Header
 * @author Nathaniel "Nat" Welch
 * @version 0.42
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

#ifndef UTIL_HEADER
#define UTIL_HEADER 

void *smalloc(int);
void *srealloc(void*, int size);
void cat(int in, int out);
pid_t sfork(void);
void spipe(int pipefd[2]);
int setblock(int fd, int block);
int sdup2(int oldfd, int newfd);
int sclose(int fd);
void startblock(void);
void stopblock(void);

#endif

