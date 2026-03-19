#pragma once

#include "../include/joblist.h"

typedef struct {
        char *name;
        int (*func)(cmd_t*);
} mshell_cmd_t;

mshell_cmd_t* mshell_findcmd(const char *arg);

int mshell_cd(cmd_t *cmd);