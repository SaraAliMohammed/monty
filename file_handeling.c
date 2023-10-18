#include "monty.h"

/**
 * open_file - opens the file
 * @file_name_path: namepath of the file
 * Return: void
 */

void open_file(char *file_name_path)
{
	FILE *fd = fopen(file_name_path, "r");

	if (file_name_path == NULL || fd == NULL)
		err(2, file_name_path);

	read_file(fd);
	fclose(fd);
}

/**
 * read_file - reads the file
 * @fd: file descriptor pointer
 * Return: Nothing
 */

void read_file(FILE *fd)
{
	int line_number = 1, format = 0;
	char *buffer = NULL;
	size_t length = 0;

	while (getline(&buffer, &length, fd) != -1)
	{
		format = parse_line(buffer, line_number, format);
		line_number++;
	}
	free(buffer);
}

/**
 * parse_line - Separates each line into tokens to determine
 *	which function to call
 * @buffer: the file line to be parsed
 * @line_number: number of the line
 * @format: storage format:
 *		If 0 Nodes will be entered as a stack.
 *		If 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack,
 *		1 if queue.
 */

int parse_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delimiter = "\n ";

	if (!buffer)
		err(4);

	opcode = strtok(buffer, delimiter);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delimiter);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	handel_operation(opcode, value, line_number, format);
	return (format);
}

/**
 * handel_operation - find the appropriate operation for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @ln: line number.
 * @format: storage format:
 *		If 0 Nodes will be entered as a stack.
 *		If 1 nodes will be entered as a queue.
 * Return: Nothing
 */
void handel_operation(char *opcode, char *value, int ln, int format)
{
	int index = 0, flag = 1;

	instruction_t operation_list[] = {
		{"push", push_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	if (opcode[0] == '#')
		return;

	while (operation_list[index].opcode)
	{
		if (strcmp(opcode, operation_list[index].opcode) == 0)
		{
			exec_fun(operation_list[index].f, opcode, value, ln, format);
			flag = 0;
		}
		index++;
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * exec_fun - Executes the required function.
 * @func: Pointer to the operation that is about to be executed.
 * @opcode: string representing the opcode.
 * @value: string representing a numeric value.
 * @ln: the instruction line numeber.
 * @format: Format specifier:
 *		If 0 Nodes will be entered as a stack.
 *		If 1 nodes will be entered as a queue.
 */
void exec_fun(op_func func, char *opcode, char *value, int ln, int format)
{
	stack_t *node;
	int flag;
	int index = 0;

	flag = 1;
	if (strcmp(opcode, "push") == 0)
	{
		if (value && value[0] == '-')
		{
			value = value + 1;
			flag = -1;
		}
		if (!value)
			err(5, ln);
		while (value[index] != '\0')
		{
			if (isdigit(value[index]) == 0)
				err(5, ln);
			index++;
		}
		node = create_node(atoi(value) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
