#include <minishell.h>
#include <minunit.h>

MU_TEST(test_should_remove_specified_arg_from_argv) {
	char	**argv = ft_split("cat Makefile 2>> outfile | cat", ' ');
	int		i = 0;

	ft_remove_arg(argv, "cat");
	ft_remove_arg(argv, "2>>");
	ft_remove_arg(argv, "cat");

	mu_check(ft_strncmp(argv[0], "Makefile", ft_strlen("Makefile") + 1) == 0);
	mu_check(ft_strncmp(argv[1], "outfile", ft_strlen("outfile") + 1) == 0);
	mu_check(ft_strncmp(argv[2], "|", 2) == 0);

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

MU_TEST(test_ft_find_arg_should_return_address_specified_arg) {
	char	**argv = ft_split("cat Makefile 2>> outfile", ' ');
	char	**found = ft_find_arg(argv, "Makefile");

	mu_check(found != NULL);
	mu_check(found[0] == argv[1]);

	found = ft_find_arg(argv, "2>>");
	mu_check(found != NULL);
	mu_check(found[0] == argv[2]);

	found = ft_find_arg(argv, "hello world");
	mu_check(found == NULL);

	int	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

MU_TEST(test_ft_find_arg_should_return_NULL_when_argv_empty) {
	char	**argv = ft_split("", ' ');
	char	**found = ft_find_arg(argv, "cat");

	mu_check(found == NULL);
	free(argv[0]);
	free(argv);
}

MU_TEST_SUITE(test_utils_args) {
	MU_RUN_TEST(test_ft_find_arg_should_return_address_specified_arg);
	MU_RUN_TEST(test_ft_find_arg_should_return_NULL_when_argv_empty);
	MU_RUN_TEST(test_should_remove_specified_arg_from_argv);
}
