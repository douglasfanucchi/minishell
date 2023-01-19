#include <stdio.h>
#include <minunit.h>
#include <minishell.h>

MU_TEST(test_space_delimiter) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "ls -l";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "ls", ft_strlen("ls") + 1) == 0);
	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, "-l", ft_strlen("-l") + 1) == 0);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);

	input = "cat infile";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "cat", ft_strlen("cat") + 1) == 0);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
}

MU_TEST(test_space_delimiter_with_quoting) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "echo \"douglas fanucchi\"";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(
		ft_strncmp(
			token->original, 
			"\"douglas fanucchi\"", 
			ft_strlen("\"douglas fanucchi\"") + 1
		) == 0
	);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);

	input = "echo 'douglas fanucchi'";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(
		ft_strncmp(
			token->original, 
			"'douglas fanucchi'", 
			ft_strlen("'douglas fanucchi'") + 1
		) == 0
	);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
}

MU_TEST(test_tab_delimiter) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "echo\t\"douglas\tfanucchi\"";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(
		ft_strncmp(
			token->original, 
			"\"douglas\tfanucchi\"", 
			ft_strlen("\"douglas\tfanucchi\"") + 1
		) == 0
	);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
}

MU_TEST(test_newline_delimiter) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "echo\n\"douglas\nfanucchi\"";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(
		ft_strncmp(
			token->original, 
			"\"douglas\nfanucchi\"", 
			ft_strlen("\"douglas\nfanucchi\"") + 1
		) == 0
	);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
}

MU_TEST_SUITE(test_tokenizer) {
	MU_RUN_TEST(test_space_delimiter);
	MU_RUN_TEST(test_space_delimiter_with_quoting);
	MU_RUN_TEST(test_tab_delimiter);
	MU_RUN_TEST(test_newline_delimiter);
}
