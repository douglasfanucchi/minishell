#include <minishell.h>
#include <minunit.h>

MU_TEST(test_analyse_pipe_token) {
	t_list		**tokens;
	char		*input;
	char		*result;
	t_token 	*token;

	input = "|";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	result = ft_analyse_token(*tokens);
	mu_check(result == token->original);
	ft_del_tokens(tokens);

	input = "cat | ls";
	tokens = ft_tokenizer(input);
	mu_check(ft_analyse_token((*tokens)->next) == NULL);
	ft_del_tokens(tokens);
}

MU_TEST(test_analyses_quoted_token) {
	t_list	**tokens;
	char	*input;
	char	*unexpected_token;
	t_token	*token;
	
	input = "'douglas fanucchi";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	unexpected_token = ft_analyse_token(*tokens);
	mu_check(unexpected_token == token->original);
	ft_del_tokens(tokens);

	input = "'douglas fanucchi'";
	tokens = ft_tokenizer(input);
	unexpected_token = ft_analyse_token(*tokens);
	mu_check(unexpected_token == NULL);
	ft_del_tokens(tokens);

	input = "'|douglas fanucchi'";
	tokens = ft_tokenizer(input);
	unexpected_token = ft_analyse_token(*tokens);
	mu_check(unexpected_token == NULL);
	ft_del_tokens(tokens);
}

MU_TEST(test_analyses_redirection_token) {
	char		*input;
	t_list		**tokens;
	t_token		*token;
	t_token		*next_token;
	char		*result;

	input = "echo 'testing' > output";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->next->content;
	result = ft_analyse_token((*tokens)->next->next);
	mu_check(result == NULL);
	ft_del_tokens(tokens);

	input = "<<>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	next_token = (*tokens)->next->content;
	result = ft_analyse_token(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);

	input = "<<0>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	next_token = (*tokens)->next->content;
	result = ft_analyse_token(*tokens);
	mu_check(result == next_token->original);
	ft_del_tokens(tokens);
}

MU_TEST_SUITE(test_analyse_token) {
	MU_RUN_TEST(test_analyse_pipe_token);
	MU_RUN_TEST(test_analyses_quoted_token);
	MU_RUN_TEST(test_analyses_redirection_token);
}
