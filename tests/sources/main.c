#include <minishell.h>
#include <minunit.h>

#include "tokens/token.c"

int	main(int argc, char **argv)
{
	MU_RUN_SUITE(test_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
