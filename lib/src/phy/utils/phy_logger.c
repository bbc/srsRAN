/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "srslte/phy/utils/phy_logger.h"
#include "srslte/srslte.h"
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
/*********************************************************************
    Functions for external logging
*********************************************************************/
static phy_log_handler_t phy_log_handler;
static void*             callback_ctx = NULL;

void srslte_phy_log_register_handler(void* ctx, phy_log_handler_t handler)
{
  phy_log_handler = handler;
  callback_ctx    = ctx;
  handler_registered++;
}

void srslte_phy_log_print(phy_logger_level_t log_level, const char* format, ...)
{
  char    tmp[256];
  va_list args;
  va_start(args, format);
  if (phy_log_handler) {
    if (vsnprintf(tmp, 256, format, args) > 0) {
      phy_log_handler(log_level, callback_ctx, tmp);
    }
  }
  va_end(args);
}