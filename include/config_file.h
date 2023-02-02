#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./config.h"
#include "./logging.h"
#include "./round_robin.h"
#include "./target_group.h"
#include "./utils.h"

void read_config_file();

#endif  // CONFIG_FILE_H