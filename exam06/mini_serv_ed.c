#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/select.h> // select
#include <stdlib.h> // malloc
#include <stdio.h>

typedef struct s_client {
    int id;
    char *buf;

} t_client;

t_client clients[4096];
char rbuff[1024 + 1];
char wbuff[1024];

fd_set activefds, readfds, writefds;

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


int main(int argc, char **argv) {
    
    if (argc != 2)
    {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    int port = atoi(argv[1]);

    // socket create and verification
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
        write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
	}

    FD_ZERO(&activefds);
    FD_SET(sockfd, &activefds);

    int maxfd = sockfd;
    int nextid = 0;

    socklen_t len;
    struct sockaddr_in servaddr, cli;
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
        write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
	}

	if (listen(sockfd, 10) < 0) {
        write(2, "Fatal error\n", strlen("Fatal error\n"));
        exit(1);
	}

    while(1)
    {
        readfds = writefds = activefds;
        if (select(maxfd + 1, &readfds, &writefds, NULL, NULL) < 0)
        {
            write(2, "Fatal error\n", strlen("Fatal error\n"));
            exit(1);
        }

        for(int fd = 0; fd <= maxfd; fd++)
        {
            if(!FD_ISSET(fd, &readfds))
                continue;

            if (fd == sockfd)
            {
                len = sizeof(cli);
                int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                if (connfd >= 0) {
                    // new client
                    if(maxfd < connfd)
                        maxfd = connfd;
                    FD_SET(connfd, &activefds);
                    clients[connfd].id = nextid++;
                    clients[connfd].buf = NULL;
                    sprintf(wbuff, "server: client %d just arrived\n", clients[connfd].id);
                    for(int i = 0; i <= maxfd; i++)
                    {
                        if(FD_ISSET(i, &writefds) && i != connfd && i != sockfd)
                        {
                            send(i, wbuff, strlen(wbuff), 0);
                        }
                    }
                    break;
                }

            }
            else
            {
                // client talk
                int r_bytes = recv(fd, rbuff, sizeof(rbuff) - 1, 0);
                if( r_bytes <= 0)
                {
                    // client disconnect
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
                    // broadcast
                    rbuff[r_bytes] = '\0';
                    clients[fd].buf = str_join(clients[fd].buf, rbuff);
                    if(!clients[fd].buf)
                    {
                        write(2, "Fatal error\n", strlen("Fatal error\n"));
                        exit(1);
                    }

                    char *msg;
                    while(extract_message(&clients[fd].buf, &msg))
                    {
                        sprintf(wbuff, "client %d: ", clients[fd].id);
                        for(int i = 0; i <= maxfd; i++)
                        {
                            if(FD_ISSET(i, &writefds) && i != fd && i != sockfd)
                            {
                                send(i, wbuff, strlen(wbuff), 0);
                            }
                        }

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