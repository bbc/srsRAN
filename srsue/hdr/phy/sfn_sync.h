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

#ifndef SRSUE_SFN_SYNC_H
#define SRSUE_SFN_SYNC_H

#include "srslte/interfaces/ue_interfaces.h"
#include "srslte/radio/radio.h"
#include "srslte/srslte.h"

namespace srsue {

// Class to synchronize system frame number
class sfn_sync
{
public:
  typedef enum { IDLE, SFN_FOUND, SFX0_FOUND, SFN_NOFOUND, ERROR } ret_code;
  sfn_sync() = default;
  ~sfn_sync();
  void     init(srslte_ue_sync_t*    ue_sync,
                const phy_args_t*    phy_args_,
                srslte::rf_buffer_t& buffer,
                uint32_t             buffer_max_samples_,
                srslte::log*         log_h,
                uint32_t             nof_subframes = SFN_SYNC_NOF_SUBFRAMES);
  void     reset();
  bool     set_cell(srslte_cell_t cell);
  ret_code run_subframe(srslte_cell_t*                               cell,
                        uint32_t*                                    tti_cnt,
                        std::array<uint8_t, SRSLTE_BCH_PAYLOAD_LEN>& bch_payload,
                        bool                                         sfidx_only = false);
  ret_code decode_mib(srslte_cell_t*                               cell,
                      uint32_t*                                    tti_cnt,
                      srslte::rf_buffer_t*                         ext_buffer,
                      std::array<uint8_t, SRSLTE_BCH_PAYLOAD_LEN>& bch_payload,
                      bool                                         sfidx_only = false);

private:
  const static int SFN_SYNC_NOF_SUBFRAMES = 100;

  const phy_args_t*   phy_args           = nullptr;
  uint32_t            cnt                = 0;
  uint32_t            timeout            = 0;
  srslte::log*        log_h              = nullptr;
  srslte_ue_sync_t*   ue_sync            = nullptr;
  srslte::rf_buffer_t mib_buffer         = {};
  uint32_t            buffer_max_samples = 0;
  srslte_ue_mib_t     ue_mib             = {};
};

}; // namespace srsue

#endif // SRSUE_SFN_SYNC_H
