#include <minishell.h>
#include <minunit.h>

MU_TEST(test_should_not_go_back_when_root) {
	t_list	**dirs = ft_newlist();
	char	*result;

	result = ft_path_after_navigate(dirs, "..");
	mu_assert_string_eq("/", result);
	free(result);

	dirs = ft_newlist();
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("usr")));

	result = ft_path_after_navigate(dirs, "../../../");
	mu_assert_string_eq("/", result);
	free(result);
}

MU_TEST(test_navigate_to_bin_from_root) {
	t_list	**dirs = ft_newlist();
	char	*result;

	result = ft_path_after_navigate(dirs, "bin");
	mu_assert_string_eq("/bin", result);
	free(result);
}

MU_TEST(test_navigate_should_go_back) {
	t_list	**dirs = ft_newlist();
	char	*result;
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("bin")));

	result = ft_path_after_navigate(dirs, "..");
	mu_assert_string_eq("/", result);
	free(result);
}

MU_TEST(test_navigate_should_go_to_absolute_path) {
	t_list	**dirs = ft_newlist();
	char	*result;
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("nfs")));
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("homes")));
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("dfanucch")));

	result = ft_path_after_navigate(dirs, "/usr/bin");
	mu_assert_string_eq("/usr/bin", result);
	free(result);

	dirs = ft_newlist();
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("nfs")));
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("homes")));
	ft_lstadd_back(dirs, ft_lstnew(ft_strdup("dfanucch")));

	result = ft_path_after_navigate(dirs, "/../../bin");
	mu_assert_string_eq("/bin", result);
	free(result);
}

MU_TEST_SUITE(test_navigate) {
	MU_RUN_TEST(test_should_not_go_back_when_root);
	MU_RUN_TEST(test_navigate_to_bin_from_root);
	MU_RUN_TEST(test_navigate_should_go_back);
	MU_RUN_TEST(test_navigate_should_go_to_absolute_path);
}
