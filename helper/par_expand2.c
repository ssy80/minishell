/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:16:10 by yoong             #+#    #+#             */
/*   Updated: 2024/10/02 13:16:20 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// perform parameter expansion only $ expansion
// move it to char[] line
// still need to do word splitting and quote removal
void	exptkn(char *s, int a[2], char *line, t_data *data)
{
	while (s[a[0]])
	{
		if (s[a[0]] == '\'')
			return (exp1q(s, a, line, data), exptkn(s, a, line, data));
		if (s[a[0]] == '"')
			return (exp2q(s, a, line, data), exptkn(s, a, line, data));
		if (s[a[0]] == '$')
			return (a[0]++, exp_s(s, a, line, data), exptkn(s, a, line, data));
		line[a[1]] = s[a[0]];
		a[0]++;
		a[1]++;
	}
}

// do not expand "|", '|', "<", '<', ">", '>', "<<", '<<', ">>",'>>'
bool	ignoreexp(char *s)
{
	if (ft_strncmp(s, "\"<\"", 4) == 0 || ft_strncmp(s, "\">\"", 4) == 0 || \
	ft_strncmp(s, "\"|\"", 4) == 0)
		return (true);
	if (ft_strncmp(s, "'<'", 4) == 0 || ft_strncmp(s, "'>'", 4) == 0 || \
	ft_strncmp(s, "'|'", 4) == 0)
		return (true);
	if (ft_strncmp(s, "\"<<\"", 5) == 0 || ft_strncmp(s, "\">>\"", 5) == 0)
		return (true);
	if (ft_strncmp(s, "'<<'", 5) == 0 || ft_strncmp(s, "'>>'", 5) == 0)
		return (true);
	return (false);
}

bool	ignoreexp2(char *s)
{
	if (ft_strncmp(s, "'\"<\"'", 4) == 0 || ft_strncmp(s, "'\">\"'", 4) == 0 || \
	ft_strncmp(s, "'\"|\"'", 4) == 0)
		return (true);
	if (ft_strncmp(s, "\"'<'\"", 4) == 0 || ft_strncmp(s, "\"'>'\"", 4) == 0 || \
	ft_strncmp(s, "\"'|'\"", 4) == 0)
		return (true);
	if (ft_strncmp(s, "'\"<<\"'", 5) == 0 || ft_strncmp(s, "'\">>\"'", 5) == 0)
		return (true);
	if (ft_strncmp(s, "\"'<<'\"", 5) == 0 || ft_strncmp(s, "\"'>>'\"", 5) == 0)
		return (true);
	return (false);
}

// use for expanding 1 tkn but need to free after using it
// should be used after word splitting
// if data is not available, set it as NULL
char	*expand1tkn(char *s, t_data *data)
{
	int		a[2];
	char	line[MAXEXP];
	char	*str;
	t_stack	stack;

	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(s, a, line, data);
	qremoval(line, &stack);
	str = ft_strdup(stack.line);
	if (str == NULL)
		return (freedatacmd(data), freenullall(data), exitcl(1), NULL);
	return (str);
}

// expand ith tkn in the data struct
// todo: add in quote removal
int	expander(char *s, t_data *data, int i)
{
	int		a[2];
	char	line[MAXEXP];
	char	*str;

	if (ignoreexp(s) || ignoreexp2(s) || \
	(i > 0 && ft_strncmp(data->cmd[i - 1], "<<", 2) == 0))
		return (1);
	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(s, a, line, data);
	str = ft_strdup(line);
	if (str == NULL)
		return (0);
	free(data->cmd[i]);
	data->cmd[i] = str;
	return (1);
}
