#ifndef HEALTH_CHECKS_H
#define HEALTH_CHECKS_H

#include "./config.h"
#include "./connection.h"
#include "./networking.h"
#include "./server.h"
#include "./utils.h"

int health_check_target(struct target_backend target);

#endif  // HEALTH_CHECKS_H