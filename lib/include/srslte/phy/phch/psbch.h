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

#ifndef SRSLTE_PSBCH_H
#define SRSLTE_PSBCH_H

#include "srslte/phy/common/phy_common_sl.h"
#include "srslte/phy/dft/dft_precoding.h"
#include "srslte/phy/fec/convolutional/convcoder.h"
#include "srslte/phy/fec/convolutional/viterbi.h"
#include "srslte/phy/fec/crc.h"
#include "srslte/phy/modem/demod_soft.h"
#include "srslte/phy/modem/modem_table.h"
#include "srslte/phy/scrambling/scrambling.h"

#define SRSLTE_SL_BCH_CRC_LEN 16

/**
 *  \brief Physical Sidelink broadcast channel.
 *
 *  Reference: 3GPP TS 36.211 version 15.6.0 Release 15 Sec. 9.6
 */
typedef struct SRSLTE_API {
  uint32_t       N_sl_id;
  srslte_sl_tm_t tm;
  srslte_cp_t    cp;

  uint32_t nof_data_re; ///< Number of RE considered during the channel mapping
  uint32_t nof_tx_re;   ///< Number of RE actually transmitted over the air (without last OFDM symbol)
  uint32_t E;
  uint32_t Qm;
  uint32_t nof_prb;
  uint32_t nof_data_symbols;
  uint32_t nof_tx_symbols;
  uint32_t sl_bch_tb_len;
  uint32_t sl_bch_tb_crc_len;
  uint32_t sl_bch_encoded_len;
  float    precoding_scaling;

  // data
  uint8_t* c;

  // crc
  srslte_crc_t crc_mib_sl;
  uint8_t*     crc_temp;

  // channel coding
  srslte_viterbi_t   dec;
  srslte_convcoder_t encoder;
  uint8_t*           d;
  int16_t*           d_16;

  // rate matching
  uint8_t* e;
  uint8_t* e_bytes; ///< To pack bits to bytes
  int16_t* e_16;

  uint8_t* codeword;
  uint8_t* codeword_bytes;
  int16_t* llr;

  // interleaving
  uint32_t* interleaver_lut;

  // scrambling
  srslte_sequence_t seq;

  // modulation
  srslte_modem_table_t mod;
  cf_t*                mod_symbols;

  // dft precoding
  srslte_dft_precoding_t dft_precoder;
  srslte_dft_precoding_t idft_precoder;
  cf_t*                  scfdma_symbols;

} srslte_psbch_t;

SRSLTE_API int
srslte_psbch_init(srslte_psbch_t* q, uint32_t nof_prb, uint32_t N_sl_id, srslte_sl_tm_t tm, srslte_cp_t cp);

SRSLTE_API void srslte_psbch_free(srslte_psbch_t* q);

SRSLTE_API int srslte_psbch_encode(srslte_psbch_t* q, uint8_t* input, uint32_t input_len, cf_t* sf_buffer);

SRSLTE_API int srslte_psbch_decode(srslte_psbch_t* q, cf_t* scfdma_symbols, uint8_t* output, uint32_t max_output_len);

SRSLTE_API int srslte_psbch_reset(srslte_psbch_t* q, uint32_t N_sl_id);

SRSLTE_API int srslte_psbch_put(srslte_psbch_t* q, cf_t* symbols, cf_t* sf_buffer);

SRSLTE_API int srslte_psbch_get(srslte_psbch_t* q, cf_t* sf_buffer, cf_t* symbols);

#endif // SRSLTE_PSBCH_H
