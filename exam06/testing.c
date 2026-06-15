#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>

typedef struct s_clients
{
	int		id;
	char*	message_buff;
}	t_client;

t_client clients[4096];
char	read_buf[1024 + 1];
char	write_buf[1024];

void fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i;

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

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	int port = atoi(argv[1]);

	int socket_fd;
	socklen_t clientlen;
	struct sockaddr_in server_addr, client_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		fatal_error();

	fd_set active_fds, read_fds, write_fds;
	FD_ZERO(&active_fds);
	FD_SET(socket_fd, &active_fds);

	int max_fd = socket_fd;
	int next_client_id = 0;

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(2130706433);
	server_addr.sin_port = htons(port);

	if (bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
		fatal_error();

	if (listen(socket_fd, SOMAXCONN) != 0)
		fatal_error();

	while (1)
	{
		read_fds = write_fds = active_fds;

		if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_fds))
				continue;
			
			if (fd == socket_fd)
			{
				clientlen = sizeof(client_addr);
				int connect_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &clientlen);
				if (connect_fd >= 0)
				{
					if (max_fd < connect_fd)
						max_fd = connect_fd;
					
					FD_SET(connect_fd, &active_fds);
					clients[connect_fd].id = next_client_id++;
					clients[connect_fd].message_buff = NULL;

					sprintf(write_buf, "server: client %d just arrived\n", clients[connect_fd].id);
					for (int i = 0; i <= max_fd; i++)
					{
						if (FD_ISSET(i, &write_fds) && i != connect_fd && i != socket_fd)
						{
							send(i, write_buf, strlen(write_buf), 0);
						}
					}
					break;
				}
				else
					fatal_error();
			}
			else
			{
				int recv_bytes = recv(fd, read_buf, sizeof(read_buf) - 1, 0);
				if (recv_bytes <= 0)
				{
					// connection lost
					sprintf(write_buf, "server: client %d just left\n", clients[fd].id);
					for (int i = 0; i <= max_fd; i++)
					{
						if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
							send(i, write_buf, strlen(write_buf), 0);
					}
					free(clients[fd].message_buff);
					FD_CLR(fd, &active_fds);
					close(fd);
					break;
				}
				else
				{
					// send message
					read_buf[recv_bytes] = '\0';
					clients[fd].message_buff = str_join(clients[fd].message_buff, read_buf);
					if (!clients[fd].message_buff)
						fatal_error();
					
					char* message;
					int	ret;
					while ((ret = extract_message(&clients[fd].message_buff, &message)) > 0)
					{
						sprintf(write_buf, "client %d: ", clients[fd].id);
						for (int i = 0; i <= max_fd; i++)
						{
							if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
							{
								send(i, write_buf, strlen(write_buf), 0);
							}
						}
						for (int i = 0; i <= max_fd; i++)
						{
							if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
							{
								send(i, message, strlen(message), 0);
							}
						}
						free(message);						
					}
					if (ret < 0)
						fatal_error();
				}
			}
		}
	}
	return (0);
}