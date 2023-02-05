#include <minishell.h>
#include <minunit.h>

#include "tokens/token.c"
#include "tokens/tokenizer.c"
#include "analyser/redirection.c"
#include "analyser/pipe.c"
#include "analyser/quoted.c"
#include "analyser/analyse.c"
#include "commands/new_command.c"
#include "commands/expansion.c"
#include "commands/quote_removal.c"
#include "redirects/new_redirect.c"
#include "utils/args.c"

char unsigned	g_bash_status;

int	main(int argc, char **argv)
{
	g_bash_status = 127;

	MU_RUN_SUITE(test_tokens);
	MU_RUN_SUITE(test_tokenizer);
	MU_RUN_SUITE(test_redirections_analyser);
	MU_RUN_SUITE(test_pipe_analyser);
	MU_RUN_SUITE(test_quoted_analyser);
	MU_RUN_SUITE(test_analyse_token);
	MU_RUN_SUITE(test_new_command);
	MU_RUN_SUITE(test_redirections);
	MU_RUN_SUITE(test_utils_args);
	MU_RUN_SUITE(test_token_expansion);
	MU_RUN_SUITE(test_quote_removal);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
