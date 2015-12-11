#include <xinu.h>
#include <stdio.h>
#include <string.h>

shellcmd xsh_udpcomm(int nargs, char *args[])
{
	int	i;			/* index into buffer		*/
	int	retval;			/* return value			*/
	//char	msg[1200]; /* message to send	*/
	char	inbuf[1500];		/* buffer for incoming reply	*/
	int32	slot;			/* UDP slot to use		*/
	int32	msglen;			/* length of outgoing message	*/
	uint32	remoteip;		/* remote IP address to use	*/
	//uint32	localip;		/* local IP address to use	*/
	uint16	echoport= 8888;		/* port number for UDP echo	*/
	uint16	locport	= 8888;	/* local port to use		*/
	int32	retries	= 3;		/* number of retries		*/
	int32	delay	= 2000;		/* reception delay in ms	*/

	/* For argument '--help', emit help about the 'udpecho' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s  REMOTEIP\n\n", args[0]);
		printf("Description:\n");
		printf("\tBounce a message off a remote UDP echo server\n");
		printf("Options:\n");
		printf("\tREMOTEIP:\tIP address in dotted decimal\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	/* Check for valid IP address argument */

	if (nargs != 3) {
		fprintf(stderr, "%s: invalid argument(s)\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	if (dot2ip(args[1], &remoteip) == SYSERR) {
		fprintf(stderr, "%s: invalid IP address argument\r\n",
			args[0]);
		return 1;
	}

	/* register local UDP port */

	slot = udp_register(remoteip, echoport, locport);
	if (slot == SYSERR) {
		fprintf(stderr, "%s: could not reserve UDP port %d\n",
				args[0], locport);
		return 1;
	}

	msglen = strnlen(args[2], 1200);
	for (i=0; i<retries; i++) {
		retval = udp_send(slot, args[2], msglen);
		if (retval == SYSERR) {
			fprintf(stderr, "%s: error sending UDP \n",
				args[0]);
			return 1;
		}

		retval = udp_recv(slot, inbuf, sizeof(inbuf), delay);
		if (retval == TIMEOUT) {
			fprintf(stderr, "%s: timeout...\n", args[0]);
			continue;
		} else if (retval == SYSERR) {
			fprintf(stderr, "%s: error from udp_recv \n",
				args[0]);
			udp_release(slot);
			return 1;
		}
		printf("%s\n",inbuf);
	}

	udp_release(slot);
	return 0;
}
