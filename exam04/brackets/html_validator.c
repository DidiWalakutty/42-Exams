#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_list
{
	char			*tag;
	struct s_list	*next;
}	t_list;

t_list	*init_node(char *tag)
{
	t_list *new = malloc(sizeof(t_list));
	new->tag = tag;
	new->next = NULL;
	return (new);
}

t_list	*lst_last(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_list **lst, t_list *new)
{
	t_list	*back;
	if (*lst)
	{
		back = lst_last(*lst);
		back->next = new;
	}
	else
		*lst = new;
}

char *extract_tag(char *str, int len)
{
	char *tag = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while (i < len && str[i] != ' ' && str[i] != '/')
	{
		tag[i] = str[i];
		i++;
	}
	tag[i] = '\0';
	return (tag);
}

int	check_words(t_list **stack, char *word, int len)
{
	if (*stack == NULL)
		return (1);

	// Create a node where we can check if the last node in the stack
	// is the same as the given closing word.
	t_list *current = *stack;
	t_list *previous = NULL;

	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	if (strncmp(current->tag, word, len) == 0)
	{
		// If they match, we pop the opening tag from the stack
		if (previous == NULL) // If there's only one tag in the stack
			*stack = NULL;
		else
			previous->next = NULL;
		free(current->tag);
		free(current);
		// We can remove this node, because it has been
		// correctly matched.
		return (0);
	}
	return (1);
}

int	validator(char *str)
{
	int	i = 0;
	t_list	*stack = NULL;

	while (str[i])
	{
		// Search for the opening tag and extract the word
		if (str[i] == '<' && str[i + 1] != '/')
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
					// If it's not 'img', we add it to the stack
					t_list *new_node = init_node(word);
					lst_add_back(&stack, new_node);
				}
			}
			i = start;
		}
		// Search for the closing tag and extract the word
		if (str[i] == '<' && str[i + 1] == '/')
		{
			int start = i + 2;
			while (str[i] != '>')
				i++;
			if (str[i] == '>')
			{
				int len = i - start;
				char *word = extract_tag(&str[start], len);
				// Check if the words and position are correct for the tag.
				if (check_words(&stack, word, len) == 1)
				{
					// It's not a match
					free(word);
					t_list *temp;
					while (stack)
					{
						temp = stack;
						stack = stack->next;
						free(temp->tag);
						free(temp); // Clean up the remaining stack
					}
					// Return an error
					return (1);
				}
				free(word);
			}
			i = start;
		}
		i++;
	}
	// If there are any unclosed tags, we free the stack and return an error.
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
	if (argv[1][0] != '\0')
	{
		if (validator(argv[1]) == 0)
		{
			printf("0\n");
			return (0);
		}
		printf("1\n");
		return (1);
	}
	return (1);
}