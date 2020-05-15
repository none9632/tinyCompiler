#include "../include/error.h"

void error(char *message)
{
	printf("error: %s\n", message);
	exit(EXIT_FAILURE);
}