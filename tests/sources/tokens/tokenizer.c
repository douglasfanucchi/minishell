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

MU_TEST(test_other_delimiters) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "cat  > 1";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "cat", 4) == 0);

	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, ">", 1) == 0);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);

	input = "cat  < 1";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;

	mu_check(ft_strncmp(token->original, "<", 1) == 0);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);

	input = "cat    | grep testing";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;

	mu_check(ft_strncmp(token->original, "|", 1) == 0);
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
}

MU_TEST(test_here_doc_and_append_tokens) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "<< limiter";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "<<", 3) == 0);

	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, "limiter", ft_strlen("limiter") + 1) == 0);
	ft_del_tokens(tokens);

	input = "<<limiter";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "<<", 3) == 0);

	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, "limiter", ft_strlen("limiter") + 1) == 0);
	ft_del_tokens(tokens);

	input = "cat Makefile >> testing";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->next->content;
	mu_check(ft_strncmp(token->original, ">>", 3) == 0);
	ft_del_tokens(tokens);

	input = "cat Makefile>> testing";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, "Makefile", ft_strlen("Makefile") + 1) == 0);

	token = (*tokens)->next->next->content;
	mu_check(ft_strncmp(token->original, ">>", 3) == 0);
	ft_del_tokens(tokens);

	input = ">>>>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, ">>", 3) == 0);
	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, ">>", 3) == 0);
	ft_del_tokens(tokens);

	input = "'<< hello'";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "'<< hello'", ft_strlen("'<< hello'") + 1) == 0);
	ft_del_tokens(tokens);
}

MU_TEST(test_redirection_token_with_specified_fd) {
	char	*input;
	t_list	**tokens;
	t_token	*token;

	input = "2 <Makefile";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "2", 2) == 0);
	ft_del_tokens(tokens);

	input = "2<Makefile";
	tokens = ft_tokenizer(input);
	token = (*tokens)->content;
	mu_check(ft_strncmp(token->original, "2<", 3) == 0);
	ft_del_tokens(tokens);

	input = "infile 1>";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->content;
	mu_check(ft_strncmp(token->original, "1>", 3) == 0);
	ft_del_tokens(tokens);

	input = "cat Makefile 2>> testing";
	tokens = ft_tokenizer(input);
	token = (*tokens)->next->next->content;
	mu_check(ft_strncmp(token->original, "2>>", 4) == 0);
	ft_del_tokens(tokens);

	tokens = ft_tokenizer("");
	token = (*tokens)->content;
	mu_check(*token->original == '\n');
	ft_del_tokens(tokens);
}

MU_TEST_SUITE(test_tokenizer) {
	MU_RUN_TEST(test_space_delimiter);
	MU_RUN_TEST(test_space_delimiter_with_quoting);
	MU_RUN_TEST(test_tab_delimiter);
	MU_RUN_TEST(test_newline_delimiter);
	MU_RUN_TEST(test_other_delimiters);
	MU_RUN_TEST(test_here_doc_and_append_tokens);
	MU_RUN_TEST(test_redirection_token_with_specified_fd);
}
