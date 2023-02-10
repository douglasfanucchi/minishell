#include <minishell.h>
#include <minunit.h>

MU_TEST(test_util_should_locate_value) {
	char	*result = ft_envp_value(g_minishell.envp, "USER");
	
	mu_assert_string_eq("douglasfanucchi", result);
	free(result);

	result = ft_envp_value(g_minishell.envp, "double_equal");
	mu_assert_string_eq("'hello=world'", result);
	free(result);
}

MU_TEST(test_util_should_not_locate_value) {
	char	*result = ft_envp_value(g_minishell.envp, "VAR_NOT_EXISTS");
	
	mu_check(result == NULL);
	free(result);
}

MU_TEST(test_util_should_change_var_value) {
	char	**envp = ft_new_envp(g_minishell.envp);
	char	*result;
	mu_check(ft_envp_update_var(envp, "SHELL", "new_minishell") == 0);
	result = ft_envp_value(envp, "SHELL");

	mu_assert_string_eq("new_minishell", result);

	free(result);

	mu_check(ft_envp_update_var(envp, "COLORTERM", "blue") == 0);
	result = ft_envp_value(envp, "COLORTERM");

	mu_assert_string_eq("blue", result);

	free(result);

	ft_del_envp(envp);
}

MU_TEST(test_util_should_remove_var) {
	char	**envp = ft_new_envp(g_minishell.envp);
	char	*result;

	mu_check(ft_envp_remove(envp, "SHELL") == 0);

	result = ft_envp_value(envp, "SHELL");
	mu_check(result == NULL);

	result = ft_envp_value(envp, "quoted_var2");
	mu_assert_string_eq("\"hello\"", result);
	free(result);

	result = ft_envp_value(envp, "AFTER_SHELL");
	mu_assert_string_eq("'its me'", result);
	free(result);

	mu_check(ft_envp_value(envp, "VAR_NOT_EXISTS") == NULL);
	ft_del_envp(envp);
}

MU_TEST_SUITE(test_envp_utils) {
	MU_RUN_TEST(test_util_should_locate_value);
	MU_RUN_TEST(test_util_should_not_locate_value);
	MU_RUN_TEST(test_util_should_change_var_value);
	MU_RUN_TEST(test_util_should_remove_var);
}
