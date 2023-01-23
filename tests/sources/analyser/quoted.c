#include <minishell.h>
#include <minunit.h>

MU_TEST(test_unclosed_quotes) {
	char	*input;
	char	*result;
	t_analyser	*analyser;
	t_list	**tokens;
	t_token	*next_token;

	analyser = get_quoted_analyser();

	input = "'douglas fanucchi";
	tokens = ft_tokenizer(input);
	next_token = (*tokens)->next->content;
	result = analyser->analyse(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);

	input = "'douglas fanucchi'\"douglas fanucchi";
	tokens = ft_tokenizer(input);
	next_token = (*tokens)->next->content;
	result = analyser->analyse(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);

	free(analyser);
}

MU_TEST(test_closed_quotes) {
	char	*input;
	char	*result;
	t_analyser	*analyser;
	t_list	**tokens;

	analyser = get_quoted_analyser();

	input = "'douglas fanucchi'";
	tokens = ft_tokenizer(input);
	result = analyser->analyse(*tokens);
	mu_check(result == NULL);
	ft_del_tokens(tokens);

	input = "'douglas fanucchi'\"douglas fanucchi\"";
	tokens = ft_tokenizer(input);
	result = analyser->analyse(*tokens);
	mu_check(result == NULL);
	ft_del_tokens(tokens);

	free(analyser);
}

MU_TEST_SUITE(test_quoted_analyser) {
	MU_RUN_TEST(test_unclosed_quotes);
	MU_RUN_TEST(test_closed_quotes);
}
