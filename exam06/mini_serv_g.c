#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>

typedef struct s_client {
    int id;
    char *buf;

} t_client;

t_client clients[4096];
char rbuff[1024 + 1];
char wbuff[1024];

void	fatal_error(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

// 1. copy functions from main
int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int main(int argc, char *argv[])
{
	// 2. start from subject
	int port;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		return 1;
	}
	else
		port = atoi(argv[1]);

	// 3. copy server logic from main till the end of listen and change messages and returns
	int sockfd;
	socklen_t len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		fatal_error();
	bzero(&servaddr, sizeof(servaddr));
	
	// 4. after server is up, do fd assigning
	fd_set activefds, readfds, writefds;
    FD_ZERO(&activefds);
    FD_SET(sockfd, &activefds);

	int maxfd = sockfd;
    int nextid = 0;
	//

	// 5. replace port
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		fatal_error();

	// 6. change to SOMAXCONN listen
	if (listen(sockfd, SOMAXCONN) != 0)
		fatal_error();
	
	// 7. whileloop

	while (1)
	{
		// 8. fds
		readfds = writefds = activefds;

		// 9. select

		if (select(maxfd + 1, &readfds, &writefds, NULL, NULL) < 0)
			fatal_error();

		// 10. go add structs and for loop
		for (int fd = 0; fd <= maxfd; fd++)
		{
			// FD_ISSET() returns nonzero if the fd is present in set, and zero if it is not.
			if (!FD_ISSET(fd, &readfds))
				continue;

			if (fd == sockfd)
            {
				// The listening socket became readable, so a new client is waiting.
                len = sizeof(cli);
                int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                if (connfd >= 0) {
					// Track the new client, give it an id, and add it to the monitored set.
                    if(maxfd < connfd)
                        maxfd = connfd;
                    FD_SET(connfd, &activefds);
                    clients[connfd].id = nextid++;
                    clients[connfd].buf = NULL;
					// Prepare the join message and broadcast it to every other writable client.
                    sprintf(wbuff, "server: client %d just arrived\n", clients[connfd].id);
                    for(int i = 0; i <= maxfd; i++)
                    {
                        // Because connfd is the newly connected client, and this message is meant for everyone except that client.
						if(FD_ISSET(i, &writefds) && i != connfd && i != sockfd)
                        {
	                        	send(i, wbuff, strlen(wbuff), 0);
                        }
                    }
                    break;
                }
				else
					fatal_error();

            }
            else
            {
				// A connected client sent data or closed the connection.
                int r_bytes = recv(fd, rbuff, sizeof(rbuff) - 1, 0);
                if( r_bytes <= 0)
                {
					// recv <= 0 means the client is gone, so notify others and clean up.
                    sprintf(wbuff, "server: client %d just left\n", clients[fd].id);
                    for(int i = 0; i <= maxfd; i++)
                    {
                        if(FD_ISSET(i, &writefds) && i != fd && i != sockfd)
                        {
	                            send(i, wbuff, strlen(wbuff), 0);
                        }
                    }
                    free(clients[fd].buf);
                    FD_CLR(fd, &activefds);
                    close(fd);
                    break;
                }
                else {
					// Keep partial input in the client's buffer until a full '\n'-terminated line exists.
                    rbuff[r_bytes] = '\0';
                    clients[fd].buf = str_join(clients[fd].buf, rbuff);
                    if(!clients[fd].buf)
	                        fatal_error();

                    char *msg;
                    while(extract_message(&clients[fd].buf, &msg))
                    {
						// For each complete line, first send the client prefix...
                        sprintf(wbuff, "client %d: ", clients[fd].id);
                        for(int i = 0; i <= maxfd; i++)
                        {
                            if(FD_ISSET(i, &writefds) && i != fd && i != sockfd)
                            {
                                send(i, wbuff, strlen(wbuff), 0);
                            }
                        }

						// ...then send the extracted message itself to the same recipients.
                        for(int i = 0; i <= maxfd; i++)
                        {
                            if(FD_ISSET(i, &writefds) && i != fd && i != sockfd)
                            {
                                send(i, msg, strlen(msg), 0);
                            }
                        }
                        free(msg);
                    }
                }
            }
		}
	}

	return 0;
}