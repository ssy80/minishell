/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:07:58 by ssian             #+#    #+#             */
/*   Updated: 2024/08/14 11:08:04 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/*static void free_split_str(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}*/

void    print_token_list(t_list *token_list)
{
    while (token_list != NULL)
    {
        printf("type: %d ", ((t_token *)(token_list->content))->type);
        printf("cmd: %s ", ((t_token *)(token_list->content))->cmd);
        printf("arg: %s ", ((t_token *)(token_list->content))->arg);
        printf("operator: %s \n", ((t_token *)(token_list->content))->operator);
        token_list =  token_list->next;
    }
}

/*equals("<", "<")*/
int equals(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

/*starts_with("<<EOF", "<<")*/
static int starts_with(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

static int is_operator(char *str)
{
    if (equals(str, "|"))
        return (1);
    if (equals(str, "<"))
        return (1);
    if (equals(str, ">"))
        return (1);
    if (equals(str, ">>"))
        return (1);
    //if (equals(str, "<<"))
    //    return (1);
    if (starts_with(str, "<<"))
        return (1);
    return (0);
}

static t_token *create_token(char *cmd, char *arg, char *operator, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (token == NULL)
        return (NULL);

    token->cmd = cmd;
    token->arg = arg;
    token->operator = operator;
    token->type = type;

    return (token);
}

static int is_prev_operator(t_list *token_list)
{
    t_list *last;

    last = ft_lstlast(token_list);
    if (last == NULL)
        return (0);
    if (((t_token *)(last->content))->type == 2) // 2 = operator
        return (1);
    return (0);
}

static int is_prev_cmd(t_list *token_list)
{
    t_list *last;

    last = ft_lstlast(token_list);
    if (last == NULL)
        return (0);
    if (((t_token *)(last->content))->type == 0) // 0 = cmd
        return (1);
    return (0);
}

static int is_prev_arg(t_list *token_list)
{
    t_list *last;

    last = ft_lstlast(token_list);
    if (last == NULL)
        return (0);
    if (((t_token *)(last->content))->type == 1) // 1 = arg
        return (1);
    return (0);
}

static int is_prev_pipe(t_list *token_list)
{
    t_list *last;

    last = ft_lstlast(token_list);
    if (last == NULL)
        return (0);
    if (((t_token *)(last->content))->type == 2) // 1 = arg
    {
        if (equals(((t_token *)(last->content))->operator, "|"))
            return (1);
    }
    return (0);
}


/*split the input str by ft_split, then */
t_list *process_raw_input(char *str)
{
    char    **split_str;
    int     i;
    t_list  *token_lst;
    t_list  *new_token;
    t_token *token;

    token_lst = NULL;
    split_str = ft_split(str, ' ');

    i = 0;

    while (split_str[i])
    {
        if (is_operator(split_str[i]))
        {
            token = create_token(NULL, NULL, split_str[i], 2);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }
        else if (!is_operator(split_str[i]) && is_prev_pipe(token_lst))//new cmd
        {
            token = create_token(split_str[i], NULL, NULL, 0);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }
        else if (!is_operator(split_str[i]) && is_prev_operator(token_lst))//new arg
        {
            token = create_token(NULL, split_str[i], NULL, 1);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }
        else if (!is_operator(split_str[i]) && is_prev_arg(token_lst))//new arg
        {
            token = create_token(NULL, split_str[i], NULL, 1);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }        
        else if (!is_operator(split_str[i]) && is_prev_cmd(token_lst))//new arg
        {
            token = create_token(NULL, split_str[i], NULL, 1);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }
        else if (!is_operator(split_str[i]) && !is_prev_cmd(token_lst))//new cmd
        {
            token = create_token(split_str[i], NULL, NULL, 0);
            new_token = ft_lstnew(token);
            ft_lstadd_back(&token_lst, new_token);
            token = NULL;
        }
        i++;
    }
    //free_split_str(split_str);
    free(split_str); //only big str to be free, small is needed as been asigned
    //print_token_list(token_lst);
    return (token_lst);
}