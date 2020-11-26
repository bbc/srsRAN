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

#ifndef SRSLTE_UE_SL_MIB_H
#define SRSLTE_UE_SL_MIB_H

#include <stdbool.h>
#include <stdint.h>

#define SRSLTE_MIB_SL_MAX_LEN 40

// 3GPP TS 36.331 Sec. 6.5.2
typedef struct SRSLTE_API {

  // sl-Bandwidth-r12 enum {6, 15, 25, 50, 75, 100} (3 bits)
  uint32_t sl_bandwidth_r12;

  // tdd-ConfigSL-r12 (3 bits)
  uint32_t tdd_config_sl_r12;

  // directFrameNumber-r12 (10 bits)
  uint32_t direct_frame_number_r12;

  // directSubframeNumber-r12 (4 bits)
  uint32_t direct_subframe_number_r12;

  // inCoverage-r12 (1 bit)
  bool in_coverage_r12;

  // reserved-r12 (19 bits)

} srslte_ue_mib_sl_t;

int srslte_ue_mib_sl_set(srslte_ue_mib_sl_t* q,
                         uint32_t            nof_prb,
                         uint32_t            tdd_config,
                         uint32_t            direct_frame_number,
                         uint32_t            direct_subframe_number,
                         bool                in_coverage);

void srslte_ue_mib_sl_pack(srslte_ue_mib_sl_t* q, uint8_t* msg);
void srlste_ue_mib_sl_unpack(srslte_ue_mib_sl_t* q, uint8_t* msg);

void srslte_ue_mib_sl_free(srslte_ue_mib_sl_t* q);

#endif // SRSLTE_UE_SL_MIB_H