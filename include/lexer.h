#pragma once

#include <stddef.h>

struct tokenlist {
        int type;
        char *data;
        int is_free;

        struct tokenlist *next;
};

enum {
        TOK_WORD,
        TOK_PIPE, // |
        TOK_REDIR_OUT, // >
        TOK_REDIR_IN, // <
        TOK_REDIR_HEREDOC, // <<
        TOK_REDIR_APPEND, // >>
        TOK_BACKGROUND, // &
        TOK_AND, // &&
        TOK_OR, // ||
        TOK_SEP, // ;
};

void toklist_free(struct tokenlist *head);
struct tokenlist* tokenize(const char *str);