#pragma once

#include "../include/joblist.h"
#include <unistd.h>

extern volatile pid_t g_fg_pid;

int execute(struct joblist *head);