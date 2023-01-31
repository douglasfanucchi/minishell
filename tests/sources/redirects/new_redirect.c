#include <minishell.h>
#include <minunit.h>
#include <stdio.h>

MU_TEST(test_redirection_should_set_new_fd_to_output_fd_by_default) {
	t_list	**tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token(">")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	t_redirect	*redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 1);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);

	tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token(">>")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 1);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);
}

MU_TEST(test_redirection_should_set_new_fd_to_input_fd_by_default) {
	t_list	**tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("infile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	t_redirect *redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 0);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);

	tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("infile")));
	redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 0);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);
}

MU_TEST(test_redirection_should_set_new_fd_to_specified_fd) {
	t_list	**tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("2>")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	t_redirect *redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 2);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);

	tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("2>>")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 2);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);

	tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("2<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 2);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);

	tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("2<<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("outfile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	redirect = ft_new_redirect(*tokens);

	mu_check(redirect->new_fd == 2);

	ft_lstclear(tokens, ft_del_token);
	free(redirect);
	free(tokens);
}

MU_TEST_SUITE(test_redirections) {
	MU_RUN_TEST(test_redirection_should_set_new_fd_to_output_fd_by_default);
	MU_RUN_TEST(test_redirection_should_set_new_fd_to_input_fd_by_default);
	MU_RUN_TEST(test_redirection_should_set_new_fd_to_specified_fd);
}
