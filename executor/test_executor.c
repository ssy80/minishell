/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:54 by ssian             #+#    #+#             */
/*   Updated: 2024/08/28 13:27:57 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void print_inout_list(t_list *inout_list)
{
	t_inout *inout;
	
	while (inout_list != NULL)
	{
		inout = (t_inout *)(inout_list->content);
		printf("inout->type: %d\n", inout->type);
		printf("inout->file: %s\n", inout->file);
		printf("inout->heredoc: %s\n", inout->heredoc);
		printf("inout->delimiter: %s\n", inout->delimiter);
		inout_list = inout_list->next;
	}
}

void print_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
}

void print_cmd(t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list != NULL)
	{
		cmd = (t_cmd *)(cmd_list->content);
		
		printf("cmd->cmd: %s\n", cmd->cmd);
		print_args(cmd->args);
		print_inout_list(cmd->inout_list);

		cmd_list = cmd_list->next;
	}
}

static t_cmd *create_cmd(char *command, char **args, t_list *inout_list)
{
    t_cmd 	*cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd == NULL)
        return (NULL);

    cmd->cmd = command;
    cmd->args = args;
    cmd->inout_list = inout_list;

    return (cmd);
}

static t_inout *create_inout(int type, char *file, char *heredoc, char *delimiter)
{
    t_inout *inout;

    inout = malloc(sizeof(t_inout));
    if (inout == NULL)
        return (NULL);

    inout->type = type;
	inout->file = file;
	inout->heredoc = heredoc;
	inout->delimiter = delimiter;

    return (inout);
}

int main()
{
	t_list  *cmd_list;
	t_cmd	*cmd;
	
	
	cmd_list = NULL;
	
	//create cmd_list (1)
	//create inout_list (1)
	t_list *inout_list;
	t_inout *inout;
	inout_list = NULL;
	//inout = create_inout(2, "aa", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//inout = create_inout(0, "b", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//inout = create_inout(0, "c", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//inout = create_inout(3, NULL, NULL, "EOF"); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//end

	char	*args[] = {"-l", "-a", NULL};
	cmd = create_cmd("ls", args, inout_list);
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	//end

    //create cmd_list (2)
	//create inout_list (2)
	inout_list = NULL;
//	inout = create_inout(3, NULL, NULL, "EOF"); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
//	ft_lstadd_back(&inout_list, ft_lstnew(inout));
//	inout = create_inout(0, "a", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
//	ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//inout = create_inout(2, "c", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//inout = create_inout(3, NULL, NULL, "EOF"); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	//ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//end

	char *args1[] = {"a", NULL};
	cmd = create_cmd("grep", args1, inout_list);
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	//end


    //create cmd_list (3)
	//create inout_list (3)
	inout_list = NULL;
	inout = create_inout(0, "aa", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	ft_lstadd_back(&inout_list, ft_lstnew(inout));
	//end

	char *args2[] = {NULL};//{"-l", NULL};
	cmd = create_cmd("wc", args2, inout_list);
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	//end

	//create cmd_list (4)
	//create inout_list (4)
	/*inout_list = NULL;
	inout = create_inout(1, "b", NULL, NULL); //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	ft_lstadd_back(&inout_list, ft_lstnew(inout));*/
	//end

	
//	char *args3[] = {"-l", NULL};
//	cmd = create_cmd("wc", args3, inout_list);
//	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	//end

	print_cmd(cmd_list);

	process_cmd_list(cmd_list);

	return (0);
}