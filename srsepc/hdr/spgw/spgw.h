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

/******************************************************************************
 * File:        spgw.h
 * Description: Top-level SP-GW class. Creates and links all
 *              interfaces and helpers.
 *****************************************************************************/

#ifndef SRSEPC_SPGW_H
#define SRSEPC_SPGW_H

#include "srslte/asn1/gtpc.h"
#include "srslte/common/buffer_pool.h"
#include "srslte/common/log_filter.h"
#include "srslte/common/logmap.h"
#include "srslte/common/threads.h"
#include <cstddef>
#include <queue>

namespace srsepc {

class mme_gtpc;

const uint16_t GTPU_RX_PORT = 2152;

typedef struct {
  std::string gtpu_bind_addr;
  std::string sgi_if_addr;
  std::string sgi_if_name;
  uint32_t    max_paging_queue;
} spgw_args_t;

typedef struct spgw_tunnel_ctx {
  uint64_t                           imsi;
  in_addr_t                          ue_ipv4;
  uint8_t                            ebi;
  srslte::gtp_fteid_t                up_ctrl_fteid;
  srslte::gtp_fteid_t                up_user_fteid;
  srslte::gtp_fteid_t                dw_ctrl_fteid;
  srslte::gtp_fteid_t                dw_user_fteid;
  bool                               paging_pending;
  std::queue<srslte::byte_buffer_t*> paging_queue;
} spgw_tunnel_ctx_t;

class spgw : public srslte::thread
{
  class gtpc;
  class gtpu;

public:
  static spgw* get_instance(void);
  static void  cleanup(void);
  int          init(spgw_args_t*                           args,
                    srslte::log_ref                        gtpu_log,
                    srslte::log_filter*                    gtpc_log,
                    srslte::log_filter*                    spgw_log,
                    const std::map<std::string, uint64_t>& ip_to_imsi);
  void         stop();
  void         run_thread();

private:
  spgw();
  virtual ~spgw();
  static spgw* m_instance;

  spgw_tunnel_ctx_t* create_gtp_ctx(struct srslte::gtpc_create_session_request* cs_req);
  bool               delete_gtp_ctx(uint32_t ctrl_teid);

  bool                      m_running;
  srslte::byte_buffer_pool* m_pool;
  mme_gtpc*                 m_mme_gtpc;

  // GTP-C and GTP-U handlers
  gtpc* m_gtpc;
  gtpu* m_gtpu;

  // Logs
  srslte::log_filter* m_spgw_log;
};

} // namespace srsepc
#endif // SRSEPC_SPGW_H
