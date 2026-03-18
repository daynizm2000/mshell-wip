#include "../include/prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

static char *get_distr(void)
{
        FILE *f = fopen("/etc/os-release", "r");
        if (!f) return NULL;

        char buffer[1024];

        while (fgets(buffer, sizeof(buffer), f)) {
                if (strncmp(buffer, "NAME=", 5) == 0) {
                        char *ptr = (*(buffer + 6) == '\"') ? buffer + 7 : buffer + 6;
                        
                        size_t j = 0;
                        while (ptr[j] != '\"' && ptr[j] != '\n') j++;

                        ptr[j] = '\0';

                        return strdup(ptr);
                }
        }

        return NULL;
}

static char *get_uname(void)
{
        struct passwd *pwd = getpwuid(getuid());

        if (pwd && pwd->pw_name) {
                return strdup(pwd->pw_name);
        }
        else {
                return NULL;
        }
}

static char* _get_home_path(void)
{
        struct passwd *pwd = getpwuid(getuid());

        if (pwd && pwd->pw_name) {
                size_t rsize = strlen(pwd->pw_name) + 7;
                char *res = malloc(rsize);
                if (!res) return NULL;

                sprintf(res, "/home/%s", pwd->pw_name);
                res[rsize] = '\0';

                return res;
        }
        
        return NULL;
}

static char *get_path(void)
{
        char *path = getcwd(NULL, 0);
        if (!path) return NULL;

        size_t len_path = strlen(path);

        char *home_path = _get_home_path();
        if (!home_path) return NULL;

        size_t len_home_path = strlen(home_path);

        if (len_path > len_home_path && strncmp(path, home_path, len_home_path) == 0) {
                sprintf(path, "~/%s", path + len_home_path + 1);
        }
        else if (len_path == len_home_path) {
                free(path);
                free(home_path);
                return strdup("~");
        }

        free(home_path);
        
        return path;
}

int prompt_init(prompt_t *prompt)
{
        if (!prompt) return -1;

        if (!(prompt->distr = get_distr())) {
                return -1;
        }

        if (!(prompt->uname = get_uname())) {
                free(prompt->distr);
                return -1;
        }

        if (!(prompt->path = get_path())) {
                free(prompt->distr);
                free(prompt->uname);
                return -1;
        }

        return 0;
}

void prompt_print(prompt_t prompt)
{
        printf("%s@%s %s>", prompt.distr, prompt.uname, prompt.path);
}

void prompt_path_update(prompt_t *prompt)
{
        if (!prompt) return;

        prompt->path = get_path();
}

void prompt_free(prompt_t *prompt)
{
        if (!prompt) return;

        if (prompt->distr) free(prompt->distr);
        if (prompt->path)  free(prompt->path);
        if (prompt->uname) free(prompt->uname);
}