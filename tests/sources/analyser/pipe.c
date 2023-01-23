#include <minishell.h>
#include <minunit.h>

MU_TEST(test_invalid_pipe_tokens) {
	t_list	**tokens;
	t_token	*token;
	char	*input;
	char	*result;
	t_analyser	*analyser;

	analyser = get_pipe_analyser();

	input = "|";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	result = analyser->analyse(*tokens);
	mu_check(result == token->original);
	ft_del_tokens(tokens);
	free(analyser);
}

MU_TEST(test_valid_pipe_tokens) {
	t_list	**tokens;
	char	*input;
	char	*result;
	t_analyser	*analyser;

	analyser = get_pipe_analyser();

	input = "cat Makefile | grep a";
	tokens = ft_tokenizer(input);
	result = analyser->analyse((*tokens)->next->next);
	mu_check(result == NULL);
	ft_del_tokens(tokens);
	free(analyser);
}

MU_TEST_SUITE(test_pipe_analyser) {
	MU_RUN_TEST(test_invalid_pipe_tokens);
	MU_RUN_TEST(test_valid_pipe_tokens);
}
