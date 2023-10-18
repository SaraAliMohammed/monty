#include "monty.h"

/**
 * print_char - Prints the Ascii value.
 * @stack: Top node of the stack pointer.
 * @line_number: The line number.
 */
void print_char(stack_t **stack, unsigned int line_number)
{
	int asc_number;

	if (!stack || !(*stack))
		string_err(11, line_number);
	asc_number = (*stack)->n;
	if (asc_number < 0 || asc_number > 127)
		string_err(10, line_number);
	printf("%c\n", asc_number);
}

/**
 * print_str - Prints a string.
 * @stack: Top node of the stack pointer.
 * @ln: The line number.
 */
void print_str(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	int asc_number;
	stack_t *temp;

	if (!stack || !(*stack))
	{
		printf("\n");
		return;
	}

	temp = *stack;
	while (temp)
	{
		asc_number = temp->n;
		if (asc_number <= 0 || asc_number > 127)
			break;
		printf("%c", asc_number);
		temp = temp->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the first node of the stack to the bottom.
 * @stack: Top node of the stack pointer.
 * @ln: The line number.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *temp;

	if (!stack || !(*stack) || (*stack)->next == NULL)
		return;

	temp = *stack;
	while (temp->next)
		temp = temp->next;

	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}


/**
 * rotr - Rotates the last node of the stack to the top.
 * @stack: Top node of the stack pointer.
 * @ln: The line number.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *temp;

	if (!stack || !(*stack) || (*stack)->next == NULL)
		return;
	temp = *stack;
	while (temp->next)
		temp = temp->next;
	temp->next = *stack;
	temp->prev->next = NULL;
	temp->prev = NULL;
	(*stack)->prev = temp;
	(*stack) = temp;
}
