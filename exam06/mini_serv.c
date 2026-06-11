#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>

typedef struct s_c
{
	int id;
	char *b;
} t_c;

typedef struct s_s
{
	int id, fd, p;
	struct pollfd fds[SOMAXCONN - 3];
	struct sockaddr_in sa, cli;
	nfds_t nfds;
	t_c c[SOMAXCONN];
} t_s;

t_s s;

int extract_message(char **buf, char **msg)
{
	char *newbuf;
	int i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = malloc(sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
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
	char *newbuf;
	int len;

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

void fatal(char *s)
{
	if (s == NULL)
	{
		write(2, "Fatal error", 11);
	}
	else
	{
		write(2, s, strlen(s));
	}
	write(2, "\n", 1);
	exit(1);
}

void bcast(char *a, int id, char *b, int add, int fd)
{
	char *str = calloc(sizeof(char), strlen(a) + strlen(b) + 8);
	if (add)
	{
		sprintf(str, "%s %i: %s", a, id, b);
	}
	else
	{
		sprintf(str, "%s %i %s", a, id, b);
	}
	int l = strlen(str);
	for (nfds_t i = 1; i < s.nfds; i++)
	{
		if (fd != s.fds[i].fd)
			send(s.fds[i].fd, str, l, MSG_NOSIGNAL);
	}
	free(str);
}

int iserv()
{
	s.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s.fd == -1)
	{
		return 0;
	}
	bzero(&s.sa, sizeof(s.sa));
	s.sa.sin_family = AF_INET;
	s.sa.sin_addr.s_addr = htonl(2130706433);
	s.sa.sin_port = htons(s.p);
	if (bind(s.fd, (const struct sockaddr *)&s.sa, sizeof(s.sa)))
	{
		return 0;
	}
	if (listen(s.fd, 10) != 0)
	{
		return 0;
	}
	s.fds[0].fd = s.fd;
	s.fds[0].events = POLLIN | POLLHUP;
	s.fds[0].revents = 0;
	s.nfds = 1;
	return 1;
}

void sloop()
{
	s.id = 0;
	while (1)
	{
		int r = poll(s.fds, s.nfds, -1);
		if (r == 0)
		{
			continue;
		}
		if (r == -1)
		{
			fatal(NULL);
		}
		if (s.fds[0].revents && POLLIN)
		{
			socklen_t l = sizeof(s.cli);
			int cfd = accept(s.fd, (struct sockaddr *)&s.cli, &l);
			if (cfd == -1)
			{
				fatal(NULL);
			}
			s.c[cfd].id = s.id++;
			s.c[cfd].b = NULL;
			s.fds[s.nfds].fd = cfd;
			s.fds[s.nfds].events = POLLIN;
			s.fds[s.nfds].revents = 0;
			s.nfds++;
			bcast("server: client", s.c[cfd].id, "just arrived\n", 0, cfd);
			r--;
		}
		if (r == 0)
		{
			continue;
		}
		for (nfds_t i = 1; i < s.nfds; i++)
		{
			if (s.fds[i].revents && POLLIN)
			{
				int fd = s.fds[i].fd;
				char buff[100];
				memset(buff, 0, 100);
				int len = recv(fd, buff, 99, MSG_NOSIGNAL);
				if (len == 0)
				{
					bcast("server: client", s.c[fd].id, "just left\n", 0, fd);
					if (s.c[fd].b != NULL)
					{
						free(s.c[fd].b);
					}
					close(fd);
					s.fds[i] = s.fds[s.nfds - 1];
					s.nfds--;
				}
				else
				{
					s.c[fd].b = str_join(s.c[fd].b, buff);
					char *msg;
					while (extract_message(&s.c[fd].b, &msg))
						bcast("client", s.c[fd].id, msg, 1, fd);
				}
			}
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		fatal("Wrong number of arguments");
	}
	s.p = atoi(av[1]);
	if (!iserv())
	{
		fatal(NULL);
	}
	sloop();
}