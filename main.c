/**
 * All right here we go!
 *
 * @author Nat Welch
 */

#include <sys/types.h>
#include <sys/dir.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>


static void finish(int sig);

void loadavg(float * a, float * b, float * c)
{
	FILE * proc = fopen("/proc/loadavg","r");
	fscanf(proc,"%e %e %e",a,b,c);
	fclose(proc);
}

int main(int argc, char *argv[])
{
	int num = 0;
	int l = 0;
	float av[3];

	/* initialize your non-curses data structures here */

	(void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

	(void) initscr();      /* initialize the curses library */
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	(void) nonl();         /* tell curses not to do NL->CR/NL on output */
	(void) cbreak();       /* take input chars one at a time, no wait for \n */
	(void) noecho();         /* echo input - in color */

	if (has_colors())
	{
		start_color();

		/*
		 * Simple color assignment, often all we need.  Color pair 0 cannot
		 * be redefined.  This example uses the same value for the color
		 * pair as for the foreground color, though of course that is not
		 * necessary:
		 */
		init_pair(1, COLOR_RED,     COLOR_BLACK);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
		init_pair(4, COLOR_BLUE,    COLOR_BLACK);
		init_pair(5, COLOR_CYAN,    COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE,   COLOR_BLACK);
	}

	for (;;)
	{
		loadavg(&av[0], &av[1], &av[2]);
		printf(" %.2f, %.2f, %.2f\r",av[0], av[1], av[2]);
		fflush(stdout);
		sleep(1);
	}

	finish(0);               /* we're done */
}

static void finish(int sig)
{
	endwin();

	/* do your non-curses wrapup here */

	exit(0);
}

