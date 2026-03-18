#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

#define DEFCAP 12

struct _tokens_macro {
        int type;
        char *data;
};

static struct _tokens_macro _tokens_fmt[] = {
        {TOK_OR,                "||"},
        {TOK_AND,               "&&"},
        {TOK_REDIR_APPEND,      ">>"},
        {TOK_REDIR_HEREDOC,     "<<"},
        {TOK_PIPE,              "|"},
        {TOK_BACKGROUND,        "&"},
        {TOK_REDIR_OUT,         ">"},
        {TOK_REDIR_IN,          "<"},
        {TOK_SEP,               ";"}
};

void toklist_free(struct tokenlist *head)
{
        if (!head) return;

        for (struct tokenlist *ptr = head; ptr != NULL; ) {
                struct tokenlist *tmp = ptr;

                if (ptr->data && ptr->is_free) free(ptr->data);

                ptr = ptr->next;
                free(tmp);
        }
}

static size_t toklist_fill(struct tokenlist *token, const char *data)
{
        for (size_t i = 0; i < sizeof(_tokens_fmt) / sizeof(*_tokens_fmt); i++) {
                if (strncmp(data, _tokens_fmt[i].data, strlen(_tokens_fmt[i].data)) == 0) {
                        token->type = _tokens_fmt[i].type;
                        token->data = _tokens_fmt[i].data;
                        token->is_free = 0;
                        
                        return strlen(token->data);
                }
        }

        size_t ccount = 0;

        if (data[0] == '\"') {
                ccount = 1;

                while (data[ccount] && data[ccount] != '\"') ccount++;
                if (data[ccount] == '\"') ccount++;

                token->data = strndup(data + 1, ccount - 2);
        }
        else {
                while (data[ccount] && !isspace(data[ccount])) ccount++;
                token->data = strndup(data, ccount);
        }

        token->type = TOK_WORD;
        token->is_free = 1;

        return ccount;
}

struct tokenlist* tokenize(const char *str)
{
        if (!str) return NULL;
        
        struct tokenlist *head = NULL;
        struct tokenlist **curr = &head;

        for (size_t i = 0; str[i]; ) {
                if (isspace(str[i])) {
                        i++;
                        continue;
                }

                *curr = malloc(sizeof(struct tokenlist));
                (*curr)->next = NULL;
                
                if (!(*curr)) {
                        toklist_free(head);
                        return NULL;
                }

                i += toklist_fill(*curr, str + i);
                curr = &(*curr)->next;
        }

        return head;
}