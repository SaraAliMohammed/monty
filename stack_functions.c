#include "monty.h"

/**
 * push_to_stack - push a new node to the stack.
 * @new_node: new node pointer.
 * @ln: The line number of of the opcode.
 */
void push_to_stack(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *temp;

	if (!new_node || !(*new_node))
		exit(EXIT_FAILURE);
	if (!head)
	{
		head = *new_node;
		return;
	}
	temp = head;
	head = *new_node;
	head->next = temp;
	temp->prev = head;
}

/**
 * print_stack - Prints the nodes of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: the line number.
 */
void print_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (!stack)
		exit(EXIT_FAILURE);
	temp = *stack;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * pop_top - Removes the top node from the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: the line number of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!stack || !(*stack))
		more_err(7, line_number);

	temp = *stack;
	*stack = temp->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * print_top - Prints the top node of the stack.
 * @stack: Top node of the stack pointer.
 * @line_number: The line number.
 */
void print_top(stack_t **stack, unsigned int line_number)
{
	if (!stack || !(*stack))
		more_err(6, line_number);
	printf("%d\n", (*stack)->n);
}
