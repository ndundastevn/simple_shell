#include "myshell.h"


/**
 * add_node - Adds a new node to the beginning of a linked list
 *
 * @head: Double pointer to the head of the linked list
 * @str: Pointer to the string to be stored in the new node
 * @num: Integer to be stored in the new node
 *
 * Return: Pointer to the newly added node, or NULL on failure
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a new node to the end of a linked list
 *
 * @head: Double pointer to the head of the linked list
 * @str: Pointer to the string to be stored in the new node
 * @num: Integer to be stored in the new node
 *
 * Return: Pointer to the newly added node, or NULL on failure
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * print_list_str - Prints the string values of each node in a linked list
 *
 * @h: Pointer to the head of the linked list
 *
 * Return: Number of nodes printed
 */
size_t print_list_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_eputsft(h->str ? h->str : "(nil)");
		_eputsft("\n");
		h = h->next;
		k++;
	}
	return (k);
}



/**
 * delete_node_at_index - Deletes a node at a given index in a linked list
 *
 * @head: Double pointer to the head of the linked list
 * @index: Index of node to be deleted
 *
 * Return: 1
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees a linked list.
 *
 * @head_ptr: A pointer to a pointer to the head of the list.
 *
 * Return: None.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

