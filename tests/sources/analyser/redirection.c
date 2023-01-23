#include <minishell.h>
#include <minunit.h>

MU_TEST(test_input_redirection_analyser) {
	char		*input;
	t_list		**tokens;
	t_token		*token;
	t_token		*next_token;
	t_analyser	*analyser;
	char		*result;

	analyser = get_redirection_analyser();

	input = "echo 'testing' > output";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->next->content;
	result = analyser->analyse((*tokens)->next->next);
	mu_check(result == NULL);
	ft_del_tokens(tokens);

	input = "<<>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	next_token = (*tokens)->next->content;
	result = analyser->analyse(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);

	input = "<<0>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	next_token = (*tokens)->next->content;
	result = analyser->analyse(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);

	free(analyser);
}

MU_TEST_SUITE(test_redirections_analyser) {
	MU_RUN_TEST(test_input_redirection_analyser);
}
