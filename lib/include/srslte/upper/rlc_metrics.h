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

#ifndef SRSLTE_RLC_METRICS_H
#define SRSLTE_RLC_METRICS_H

#include "srslte/common/common.h"
#include <iostream>

namespace srslte {

typedef struct {
  // SDU metrics
  uint32_t num_tx_sdus;
  uint32_t num_rx_sdus;
  uint64_t num_tx_sdu_bytes;
  uint64_t num_rx_sdu_bytes;
  uint32_t num_lost_sdus; //< Count dropped SDUs at Tx due to bearer inactivity or empty buffer

  // PDU metrics
  uint32_t num_tx_pdus;
  uint32_t num_rx_pdus;
  uint64_t num_tx_pdu_bytes;
  uint64_t num_rx_pdu_bytes;
  uint32_t num_lost_pdus;    //< Lost PDUs registered at Rx
} rlc_bearer_metrics_t;

typedef struct {
  rlc_bearer_metrics_t bearer[SRSLTE_N_RADIO_BEARERS];
  rlc_bearer_metrics_t mrb_bearer[SRSLTE_N_MCH_LCIDS];
} rlc_metrics_t;

} // namespace srslte

#endif // SRSLTE_RLC_METRICS_H
