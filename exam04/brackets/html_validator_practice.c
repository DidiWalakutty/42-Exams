#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_list
{
	char		*tag;
	struct s_list *next;
}	t_list;

t_list	*init_node(char *word)
{
	t_list *new = malloc(sizeof(t_list));
	new->tag = word;
	new->next = NULL;
	return (new);
}

t_list	*last_node(t_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

void	lst_add_back(t_list **lst, t_list *new_node)
{
	t_list *back;

	if (*lst)
	{
		back = last_node(*lst);
		back->next = new_node;
	}
	else
		*lst = new_node;
}

char	*extract_tag(char *str, int len)
{
	int i = 0;
	char *word = malloc(sizeof(char) * (len + 1));

	while (i < len && str[i] != ' ' && str[i] != '/')
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	check_words(t_list **stack, char *word, int len)
{
	// practice
}

int	validator(char *str)
{
	int i = 0;
	t_list	*stack = NULL;

	while (str[i])
	{
		if (str[i] == '<' && str[i] != '/')
		{
			int start = i + 1;
			while (str[i] != '>')
				i++;
			if (str[i] == '>')
			{
				int len = i - start;
				char *word = extract_tag(&str[start], len);
				if (strncmp(word, "img", 3) == 0)
					i = start;
				else
				{
					t_list *new_node = init_node(word);
					lst_add_back(&stack, new_node);
				}
			}
			i = start;
		}
		if (str[i] == '<' && str[i + 1] == '/')
		{
			int start = i + 2;
			while (str[i] != '>')
				i++;
			if (str[i] == '>')
			{
				int len = i - start;
				char *word = extract_tag(&str[start], len);
				if (check_words(&stack, word, len) == 1)
				{
					free(word);
					t_list *temp;
					while (stack)
					{
						temp = stack;
						stack = stack->next;
						free(temp->tag);
						free(temp);
					}
					return (1);
				}
				free(word);
			}
			i = start;
		}
		i++;
	}
	// practice
	if (stack != NULL)
	{
		t_list *temp;
		while (stack)
		{
			temp = stack;
			stack = stack->next;
			free(temp->tag);
			free(temp);
		}
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (argv[1][0] != '/0')
	{
		if (validator(argv[1]) == 0)
		{
			printf("0\n");
			return (0);
		}
		printf("1\n");
		return (1);
	}
}