#include <minishell.h>
#include <minunit.h>

#include "tokens/token.c"
#include "tokens/tokenizer.c"

int	main(int argc, char **argv)
{
	MU_RUN_SUITE(test_tokens);
	MU_RUN_SUITE(test_tokenizer);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
