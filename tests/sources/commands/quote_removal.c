#include <minishell.h>
#include <minunit.h>

char	**env;
char	**path;

MU_TEST(test_should_remove_quotes_acting_as_quoting) {
	t_command	*command = ft_new_command(ft_tokenizer("'hello world'"), env, path);
	char		*assert_str = "hello world";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("only'$one'arg"), env, path);
	assert_str = "only$onearg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("my'arg'"), env, path);
	assert_str = "myarg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("only'$one''arg'"), env, path);
	assert_str = "only$onearg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("\"hello\"'world'"), env, path);
	assert_str = "helloworld";

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_shouldnot_remove_quotes_not_acting_as_quoting) {
	t_command	*command = ft_new_command(ft_tokenizer("'\"$?\"'"), env, path);
	char		*assert_str = "\"$?\"";

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str)) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_not_remove_quotes_that_was_expanded) {
	t_command	*command = ft_new_command(ft_tokenizer("$quoted_var"), env, path);
	char		*assert_str = "'hello'";
	ft_expand_args(command);

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("\"$quoted_var\""), env, path);
	assert_str = "'hello'";
	ft_expand_args(command);

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST_SUITE(test_quote_removal) {
	env = ft_split("SHELL=minishell\nPATH=/usr/bin\nUSER=fanucchi\nquoted_var='hello'", '\n');
	path = (char **)ft_split("/usr/bin:", ':');

	MU_RUN_TEST(test_should_remove_quotes_acting_as_quoting);
	MU_RUN_TEST(test_shouldnot_remove_quotes_not_acting_as_quoting);
	MU_RUN_TEST(test_should_not_remove_quotes_that_was_expanded);

	int i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}