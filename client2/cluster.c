#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cluster.h"

# define PORT 1977

int	main(int argc, char **argv)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(0);
	}
	struct hostent *hostinfo = NULL;
	SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */

	hostinfo = gethostbyname(argv[1]); /* on récupère les informations de l'hôte auquel on veut se connecter */

	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
		fprintf (stderr, "Unknown host %s.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	sin.sin_port = htons(PORT); /* on utilise htons pour le port */
	sin.sin_family = AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		perror("connect()");
		exit(0);
	}

	char buffer[1024];
	while (1)
	{
		if (scanf("%s", buffer) != 1)
			break;
		if(send(sock, buffer, strlen(buffer), 0) < 0)
		{
			perror("send()");
			exit(0);
		}
	}
	closesocket(sock);
	return (0);
}
