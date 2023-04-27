#include "myshell.h"

/**
 * list_len - calculates the length of a linked list
 * @f: pointer to the head of the linked list
 *
 * Return: the length of the linked list
 */
size_t list_len(const list_t *f)
{
	size_t k = 0;

	while (f)
	{
		f = f->next;
		k++;
	}
	return (k);
}

/**
 * list_to_stringsnow - converts a linked list to an array of strings
 * @head: pointer to the head of the linked list
 *
 * Return: a pointer to an array of strings
 */
char **list_to_stringsnow(list_t *head)
{
	list_t *node = head;
	size_t k = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < k; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}

/**
 * print_list - prints the contents of a linked list
 * @f: pointer to the head of the linked list
 *
 * Return: the length of the linked list
 */
size_t print_list(const list_t *f)
{
	size_t k = 0;

	while (f)
	{
		_eputsft(convert_number(f->num, 10, 0));
		_eputcharr(':');
		_eputcharr(' ');
		_eputsft(f->str ? f->str : "(nil)");
		_eputsft("\n");
		f = f->next;
		k++;
	}
	return (k);
}


/**
 * node_starts_with - finds node with a given prefix and character
 * @node: pointer to the head of the linked list
 * @prefix: the prefix to search for
 * @c: the character to match, or -1 to match any character
 *
 * Return: a pointer to the first node , or NULL if no node matches
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - finds the index of a node in a linked list
 * @head: pointer to the head of the linked list
 * @node: pointer to the node to find the index of
 *
 * Return: the linked list, or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
