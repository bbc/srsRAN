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

#include "srslte/mac/pdu_queue.h"
#include "srslte/common/log_helper.h"

namespace srslte {

void pdu_queue::init(process_callback* callback_, log_ref log_h_)
{
  callback = callback_;
  log_h    = log_h_;
}

uint8_t* pdu_queue::request(uint32_t len)
{
  if (len > MAX_PDU_LEN) {
    ERROR("Error request buffer of invalid size %d. Max bytes %d\n", len, MAX_PDU_LEN);
    return NULL;
  }
  pdu_t* pdu = pool.allocate("pdu_queue::request", true);
  if (!pdu) {
    if (log_h) {
      log_h->error("Not enough buffers for MAC PDU\n");
    }
    ERROR("Not enough buffers for MAC PDU\n");
  }
  if ((void*)pdu->ptr != (void*)pdu) {
    ERROR("Fatal error in memory alignment in struct pdu_queue::pdu_t\n");
    exit(-1);
  }

  return pdu->ptr;
}

void pdu_queue::deallocate(uint8_t* pdu)
{
  if (!pool.deallocate((pdu_t*)pdu)) {
    log_h->warning("Error deallocating from buffer pool in deallocate(): buffer not created in this pool.\n");
  }
}

/* Demultiplexing of logical channels and dissassemble of MAC CE
 * This function enqueues the packet and returns quicly because ACK
 * deadline is important here.
 */
void pdu_queue::push(uint8_t* ptr, uint32_t len, channel_t channel)
{
  if (ptr) {
    pdu_t* pdu   = (pdu_t*)ptr;
    pdu->len     = len;
    pdu->channel = channel;
    pdu_q.push(pdu);
  } else {
    log_h->warning("Error pushing pdu: ptr is empty\n");
  }
}

bool pdu_queue::process_pdus()
{
  bool     have_data = false;
  uint32_t cnt       = 0;
  pdu_t*   pdu;
  while (pdu_q.try_pop(&pdu)) {
    if (callback) {
      callback->process_pdu(pdu->ptr, pdu->len, pdu->channel);
    }
    cnt++;
    have_data = true;
  }
  if (cnt > 20) {
    if (log_h) {
      log_h->warning("PDU queue dispatched %d packets\n", cnt);
    }
    printf("Warning PDU queue dispatched %d packets\n", cnt);
  }
  return have_data;
}

void pdu_queue::reset()
{
  pdu_t* pdu;
  while (pdu_q.try_pop(&pdu)) {
    // nop
  }
}

} // namespace srslte
