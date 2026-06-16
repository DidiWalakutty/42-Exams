#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

// add
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

/**
 * @ brief mini_serv has 5 jobs
 * 
 * 1. Create server socket
 * 2. Wait for events with select()
 * 3. Accept new clients and broadcast their arrival
 * 4. Receive messages from clients, broadcast them
 * 5. Handle disconnections
 */

typedef struct s_client 
{
	int 	id;
	char	*message_buffer;
} t_client;

t_client clients[4096];			// 4096 is the max number of fds, so we can use fd as index to store client info
char receive_buff[1024 + 1];	// buffer for receiving data, +1 for null terminator
char write_buff[1024];			// buffer for sending data

void	fatal_error(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

// you can copy extract_message and str_join from given main. 
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
	socklen_t client_len;							// length of client address structure
	struct sockaddr_in server_addr, client_addr;	// server and client address structures
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		fatal_error();
	
	fd_set active_fds, read_fds, write_fds;
	FD_ZERO(&active_fds); 					// Initialize the active fd set
	FD_SET(socket_fd, &active_fds); 		// Add the listening socket to the active

	int max_fd = socket_fd;
	int next_client_id = 0;


	bzero(&server_addr, sizeof(server_addr));
	// given in main:
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(2130706433);
	server_addr.sin_port = htons(port);

	if (bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
		fatal_error();
	
	if (listen(socket_fd, SOMAXCONN) != 0)
		fatal_error();

	while (1)
	{
		read_fds = write_fds = active_fds; // Copy the active fd set to readfds and writefds for select
		
		// Wait for events with select()
		if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_fds))
				continue;
			
				if (fd == socket_fd)
				{
				// new client connection
				client_len = sizeof(client_addr);
				int connect_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
				if (connect_fd >= 0)
				{
					if (max_fd < connect_fd)
						max_fd = connect_fd;

					FD_SET(connect_fd, &active_fds);			// Add new client socket to active
					clients[connect_fd].id = next_client_id++;	// Assign an ID to the new client
					clients[connect_fd].message_buffer = NULL;
					
					sprintf(write_buff, "server: client %d just arrived\n", clients[connect_fd].id);
					for (int i = 0; i <= max_fd; i++)
					{
						// send to all writable clients except the new client and the listening socket
						if (FD_ISSET(i, &write_fds) && i != connect_fd && i != socket_fd)
						{
							send(i, write_buff, strlen(write_buff), 0);
						}
					}
					break;
				}
				else
					fatal_error();
			}
			else
			{
				// a connected client sent data or closed the connection
				int recv_bytes = recv(fd, &receive_buff, sizeof(receive_buff) - 1, 0);
				if (recv_bytes <= 0)
				{
					// client is disconnected
					sprintf(write_buff, "server: client %d just left\n", clients[fd].id);
					for (int i = 0; i <= max_fd; i++)
					{
						if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
						{
							send(i, write_buff, strlen(write_buff), 0);
						}
					}
					free(clients[fd].message_buffer);
					FD_CLR(fd, &active_fds);
					close(fd);
					break;
				}
				else
				{
					// client sent a message
					receive_buff[recv_bytes] = '\0';
					clients[fd].message_buffer = str_join(clients[fd].message_buffer, receive_buff);
					if (!clients[fd].message_buffer)
						fatal_error();

					char *msg;
					int ret;
					while ((ret = extract_message(&clients[fd].message_buffer, &msg)) > 0)
					{
						sprintf(write_buff, "client %d: ", clients[fd].id);
						for (int i = 0; i <= max_fd; i++)
						{
							if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
							{
								send(i, write_buff, strlen(write_buff), 0);
							}
						}
						for (int i = 0; i <= max_fd; i++)
						{
							if (FD_ISSET(i, &write_fds) && i != fd && i != socket_fd)
							{
								send(i, msg, strlen(msg), 0);
							}
						}
						free(msg);
					}
					if (ret < 0)
						fatal_error();
				}
			}
		}	
	}
	return 0;
}