#include "monty.h"

/**
 * mul_nodes - Multiplies the top two elements of the stack.
 * @stack: Top node of the stack pointer.
 * @line_number: The line number.
 */
void mul_nodes(stack_t **stack, unsigned int line_number)
{
	int mul;

	if (!stack || !(*stack) || (*stack)->next == NULL)
		more_err(8, line_number, "mul");

	(*stack) = (*stack)->next;
	mul = (*stack)->n * (*stack)->prev->n;
	(*stack)->n = mul;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * mod_nodes - Modulus the top two elements of the stack.
 * @stack: Top node of the stack pointer.
 * @line_number: The line number.
 */
void mod_nodes(stack_t **stack, unsigned int line_number)
{
	int mod;

	if (!stack || !(*stack) || (*stack)->next == NULL)
		more_err(8, line_number, "mod");

	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	mod = (*stack)->n % (*stack)->prev->n;
	(*stack)->n = mod;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
