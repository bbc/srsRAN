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

#ifndef SRSLTE_MAC_PCAP_H
#define SRSLTE_MAC_PCAP_H

#include "srslte/common/pcap.h"
#include <stdint.h>

namespace srslte {

class mac_pcap
{
public:
  mac_pcap();
  ~mac_pcap();
  void enable(bool en);
  void open(const char* filename, uint32_t ue_id = 0);
  void close();

  void set_ue_id(uint16_t ue_id);

  void
       write_ul_crnti(uint8_t* pdu, uint32_t pdu_len_bytes, uint16_t crnti, uint32_t reTX, uint32_t tti, uint8_t cc_idx);
  void write_dl_crnti(uint8_t* pdu, uint32_t pdu_len_bytes, uint16_t crnti, bool crc_ok, uint32_t tti, uint8_t cc_idx);
  void write_dl_ranti(uint8_t* pdu, uint32_t pdu_len_bytes, uint16_t ranti, bool crc_ok, uint32_t tti, uint8_t cc_idx);

  // SI and BCH only for DL
  void write_dl_sirnti(uint8_t* pdu, uint32_t pdu_len_bytes, bool crc_ok, uint32_t tti, uint8_t cc_idx);
  void write_dl_bch(uint8_t* pdu, uint32_t pdu_len_bytes, bool crc_ok, uint32_t tti, uint8_t cc_idx);
  void write_dl_pch(uint8_t* pdu, uint32_t pdu_len_bytes, bool crc_ok, uint32_t tti, uint8_t cc_idx);
  void write_dl_mch(uint8_t* pdu, uint32_t pdu_len_bytes, bool crc_ok, uint32_t tti, uint8_t cc_idx);

  void write_ul_rrc_pdu(const uint8_t* input, const int32_t input_len);

  // Sidelink
  void write_sl_crnti(uint8_t* pdu, uint32_t pdu_len_bytes, uint16_t rnti, uint32_t reTX, uint32_t tti, uint8_t cc_idx);

private:
  bool     enable_write;
  FILE*    pcap_file;
  uint32_t ue_id;
  void     pack_and_write(uint8_t* pdu,
                          uint32_t pdu_len_bytes,
                          uint32_t reTX,
                          bool     crc_ok,
                          uint8_t  cc_idx,
                          uint32_t tti,
                          uint16_t crnti_,
                          uint8_t  direction,
                          uint8_t  rnti_type);
};

} // namespace srslte

#endif // SRSLTE_MAC_PCAP_H
