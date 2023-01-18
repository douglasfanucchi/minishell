#include <minishell.h>
#include <minunit.h>

MU_TEST(test_token_creation) {
	t_token	*token;

	token = ft_new_token("ls", 0);
	mu_check(ft_strncmp(token->original, "ls", ft_strlen("ls") + 1) == 0);
	mu_check(ft_strncmp(token->expanded, token->original, ft_strlen(token->original) + 1) == 0);
	mu_check(!token->should_expand);
	ft_del_token(token);

	token = ft_new_token("$?", 1);
	mu_check(token->should_expand);
	ft_del_token(token);

	token = ft_new_token("$any_var", 1);
	mu_check(token->should_expand);
	ft_del_token(token);
}

MU_TEST_SUITE(test_tokens) {
	MU_RUN_TEST(test_token_creation);
}
