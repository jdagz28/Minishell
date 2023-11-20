/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 21:33:15 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

const char *token_kind_strings[] = {
    "TK_WORD",
    "TK_PIPE",
    "TK_OR",
    "TK_AND",
    "TK_SEMICOLON",
    "TK_OPEN_PARENTHESIS",
    "TK_CLOSE_PARENTHESIS",
    "TK_OPERATOR",
    "TK_REDIRECT",
    "TK_EOF"};

const char *node_type_strings[] = {
    "SIMPLE_CMD",
    "PIPE_NODE",
    "OR_NODE",
    "AND_NODE",
    "SEMICOLON_NODE"};

void print_tokens(t_token *tokens)
{
    int i;
    t_token *current;

    i = 0;
    current = tokens;
    while (current != NULL)
    {
        printf("Token %d\n", i++);
        if (current->word != NULL)
            printf("Token: \t%s\n", current->word);
        printf("Type: \t%s\n\n", token_kind_strings[current->kind]);
        current = current->next;
    }
    // free_token(tokens);
}

void print_ast_recursive(t_node *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == SIMPLE_CMD)
    {
        printf("Simple Command: ");
        for (char **arg = node->content.simple_cmd.argv; *arg != NULL; ++arg)
        {
            printf("%s ", *arg);
        }
        printf("%d %d", node->content.simple_cmd.fd_input, node->content.simple_cmd.fd_output);
        printf("\n");
    }
    else
    {
        printf("Node Type: %s\n", node_type_strings[node->type]);
        printf("Left Child:\n");
        print_ast_recursive(node->content.child.left);
        printf("Right Child:\n");
        print_ast_recursive(node->content.child.right);
    }
}

void print_ast_dot(t_node *node, FILE *output)
{
    if (node == NULL)
    {
        return;
    }

    fprintf(output, "  node%p [label=\"", (void *)node);

    if (node->type == SIMPLE_CMD)
    {
        fprintf(output, "Simple Command: ");
        for (char **arg = node->content.simple_cmd.argv; *arg != NULL; ++arg)
        {
            fprintf(output, "%s ", *arg);
        }
    }
    else
    {
        fprintf(output, "Node Type: %s", node_type_strings[node->type]);
    }

    fprintf(output, "\"];\n");

    if (node->type != SIMPLE_CMD)
    {
        if (node->content.child.left)
        {
            print_ast_dot(node->content.child.left, output);
            fprintf(output, "  node%p -> node%p [label=\"Left\"];\n", (void *)node, (void *)(node->content.child.left));
        }
        if (node->content.child.right)
        {
            print_ast_dot(node->content.child.right, output);
            fprintf(output, "  node%p -> node%p [label=\"Right\"];\n", (void *)node, (void *)(node->content.child.right));
        }
    }
}