#include "../include/joblist.h"
#include "../include/mshell_cmd.h"
#include <string.h>
#include <unistd.h>

mshell_cmd_t mshell_commands[] = {
        {"cd", mshell_cd},
};

mshell_cmd_t* mshell_findcmd(const char *arg)
{
        if (!arg) return NULL;

        for (size_t i = 0; i < sizeof(mshell_commands) / sizeof(*mshell_commands); i++) {
                if (strcmp(mshell_commands[i].name, arg) == 0) {
                        return &mshell_commands[i];
                }
        }

        return NULL;
}

int mshell_cd(cmd_t *cmd)
{
        if (!cmd) return -1;
        
        return chdir(cmd->argv[1]);
}