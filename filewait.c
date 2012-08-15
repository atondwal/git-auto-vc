/*
 * filewait - wait for an even on one of many files, then exit.
 * by Anish Tondwalkar, Jan 27, 2012
 *
 * Based heavily on:
 *   filewait - wait for an event on a file, then exit.
 *     by David Simmons, April 7, 2011
 *     http://cafbit.com/entry/file_event_notifications_in_macos
 *
 * This program is in the public domain.
 *
 * Compile this program with the following command:
 *     gcc -o filewait filewait.c
 *
 * This simple utility uses the BSD kqueue kernel facility to wait for
 * an event to occur on the specified files, then exit.  An example use
 * of this utility might be a shell script that automatically compiles
 * a program whenever the user's editor saves the source file.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

int main(int argc, char **argv)
{

	/* insist on a single argument -- the file to wait on. */
	if (argc != 2) {
		printf("usage: filewait filename\n");
		exit(1);
	}

	/* allocate a kqueue */
	int kq = kqueue();
	if (kq == -1) {
		perror("kqueue");
		exit(1);
	}

	struct kchanges changes[argv];
	for (int i = 0; i < argc - 1; i++) {
		/* open a read-only file descriptor to the specified file */
		int fd = open(argv[i + 1], O_RDONLY);
		if (fd == -1) {
			perror("open");
			exit(1);
		}

		/* define a kevent structure for waiting on file events */
		struct kevent *ke = calloc(1, sizeof(struct kevent));
		ke->ident = fd;
		ke->filter = EVFILT_VNODE;
		ke->flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
		ke->fflags =
		    NOTE_DELETE | NOTE_WRITE | NOTE_ATTRIB | NOTE_RENAME;
		ke->data = 0;
		ke->udata = 0;
		kchanges[i] = ke;
	}

	/* wait indefinitely for an event to occur on the file */
	struct kevent events[1];
	kevent(kq, kchanges, argc, events, 1, NULL);

	exit(0);
}
