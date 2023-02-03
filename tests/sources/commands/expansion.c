#include <minunit.h>
#include <minishell.h>

char	**path;
char	**env;

MU_TEST(test_token_should_not_expands) {
	char		*input = "cat Makefile | grep '$name'";
	char		**not_expanded = ft_split(input, ' ');
	t_command	*command = ft_new_command(ft_tokenizer(input), env, path);

	ft_expand_args(command);

	int i = -1;
	while (command->argv[++i])
		mu_check(ft_strncmp(not_expanded[i], command->argv[i], ft_strlen(not_expanded[i]) + 1) == 0);
	ft_del_command(command);
	i = 0;
	while (not_expanded[i])
		free(not_expanded[i++]);
	free(not_expanded);
}

MU_TEST(test_token_should_expand_to_empty_value) {
	t_list	**tokens = ft_tokenizer("cat $filename");
	t_command	*command = ft_new_command(tokens, env, path);
	char	*assert_str;

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "", 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("cat \"$filename\"");
	command = ft_new_command(tokens, env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"\"", 3) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"filename $fillename is being used\"");
	command = ft_new_command(tokens, env, path);
	assert_str = "\"filename  is being used\"";
	
	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_to_path_value) {
	t_list	**tokens = ft_tokenizer("echo \"$PATH\"");
	t_command	*command = ft_new_command(tokens, env, path);
	char *assert_str;

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"/usr/bin:/usr/sbin\"", ft_strlen("\"/usr/bin:/usr/sbin\"") + 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo $PATH");
	command = ft_new_command(tokens, env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "/usr/bin:/usr/sbin", ft_strlen("/usr/bin:/usr/sbin") + 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"the shell $SHELL is what im using\"");
	assert_str = "\"the shell minishell is what im using\"";
	command = ft_new_command(tokens, env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_to_bash_status_code) {
	t_list	**tokens = ft_tokenizer("echo $?");
	t_command	*command = ft_new_command(tokens, env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "127", 4) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"$?\"");
	command = ft_new_command(tokens, env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"127\"", 6) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_to_expand_even_with_single_quotes) {
	t_command	*command = ft_new_command(ft_tokenizer("\"'$?'\""), env, path);

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], "\"'127'\"", 6) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_two_straight_variables) {
	t_command	*command = ft_new_command(ft_tokenizer("$SHELL$PATH"), env, path);
	char		*assert_str = "minishell/usr/bin:/usr/sbin";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_expand_variable_after_quoted_variable) {
	t_command	*command = ft_new_command(ft_tokenizer("'$not'$SHELL"), env, path);
	char		*assert_str = "'$not'minishell";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_expand_quoted_straight_tokens) {
	t_command	*command = ft_new_command(ft_tokenizer("\"$SHELL$PATH\""), env, path);
	char		*assert_str = "\"minishell/usr/bin:/usr/sbin\"";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST_SUITE(test_token_expansion) {
	env = ft_split("PATH=/usr/bin:/usr/sbin\nSHELL=minishell", '\n');
	path = ft_split("/usr/bin:/usr/sbin", ':');
	
	MU_RUN_TEST(test_token_should_not_expands);
	MU_RUN_TEST(test_token_should_expand_to_empty_value);
	MU_RUN_TEST(test_token_should_expand_to_path_value);
	MU_RUN_TEST(test_token_should_expand_to_bash_status_code);
	MU_RUN_TEST(test_token_should_to_expand_even_with_single_quotes);
	MU_RUN_TEST(test_token_should_expand_two_straight_variables);
	MU_RUN_TEST(test_should_expand_variable_after_quoted_variable);
	MU_RUN_TEST(test_should_expand_quoted_straight_tokens);

	int	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}
