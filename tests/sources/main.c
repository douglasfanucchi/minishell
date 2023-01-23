#include <minishell.h>
#include <minunit.h>

#include "tokens/token.c"
#include "tokens/tokenizer.c"
#include "analyser/redirection.c"
#include "analyser/pipe.c"
#include "analyser/quoted.c"

int	main(int argc, char **argv)
{
	MU_RUN_SUITE(test_tokens);
	MU_RUN_SUITE(test_tokenizer);
	MU_RUN_SUITE(test_redirections_analyser);
	MU_RUN_SUITE(test_pipe_analyser);
	MU_RUN_SUITE(test_quoted_analyser);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
