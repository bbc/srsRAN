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
 *  File:         ue_mib.h
 *
 *  Description:  This object decodes the MIB from the PBCH of an LTE signal.
 *
 *                The function srslte_ue_mib_decode() shall be called multiple
 *                times, each passing a number of samples multiple of 19200,
 *                sampled at 1.92 MHz (that is, 10 ms of samples).
 *
 *                The function uses the sync_t object to find the PSS sequence and
 *                decode the PBCH to obtain the MIB.
 * 
 *                The function returns 0 until the MIB is decoded.
 *
 *                See ue_cell_detect.c for an example.
 *
 *  Reference:
 *****************************************************************************/

#ifndef SRSLTE_UE_MIB_H
#define SRSLTE_UE_MIB_H

#include <stdbool.h>

#include "srslte/config.h"
#include "srslte/phy/ue/ue_sync.h"
#include "srslte/phy/sync/cfo.h"
#include "srslte/phy/ch_estimation/chest_dl.h"
#include "srslte/phy/phch/pbch.h"
#include "srslte/phy/dft/ofdm.h"

#define SRSLTE_UE_MIB_NOF_PRB              6

#define SRSLTE_UE_MIB_FOUND                1
#define SRSLTE_UE_MIB_NOTFOUND             0

typedef struct SRSLTE_API {
  srslte_sync_t sfind;

  cf_t* sf_symbols;

  srslte_ofdm_t fft;
  srslte_pbch_t pbch;

  srslte_chest_dl_t     chest;
  srslte_chest_dl_res_t chest_res;

  uint8_t  bch_payload[SRSLTE_BCH_PAYLOAD_LEN];
  uint32_t nof_tx_ports; 
  uint32_t sfn_offset; 
  
  uint32_t frame_cnt; 
} srslte_ue_mib_t;

SRSLTE_API int srslte_ue_mib_init(srslte_ue_mib_t* q, cf_t* in_buffer, uint32_t max_prb);

SRSLTE_API void srslte_ue_mib_free(srslte_ue_mib_t *q);

SRSLTE_API int srslte_ue_mib_set_cell(srslte_ue_mib_t * q,
                                      srslte_cell_t cell);

SRSLTE_API void srslte_ue_mib_reset(srslte_ue_mib_t * q); 

SRSLTE_API int srslte_ue_mib_decode(srslte_ue_mib_t * q, 
                                    uint8_t bch_payload[SRSLTE_BCH_PAYLOAD_LEN], 
                                    uint32_t *nof_tx_ports, 
                                    int *sfn_offset); 


/* This interface uses ue_mib and ue_sync to first get synchronized subframes 
 * and then decode MIB
 * 
 * This object calls the pbch object with nof_ports=0 for blind nof_ports determination 
*/
typedef struct {
  srslte_ue_mib_t ue_mib; 
  srslte_ue_sync_t ue_sync;
  cf_t*            sf_buffer[SRSLTE_MAX_CHANNELS];
  uint32_t         nof_rx_channels;
} srslte_ue_mib_sync_t;

SRSLTE_API int
srslte_ue_mib_sync_init_multi(srslte_ue_mib_sync_t* q,
                              int(recv_callback)(void*, cf_t* [SRSLTE_MAX_CHANNELS], uint32_t, srslte_timestamp_t*),
                              uint32_t nof_rx_channels,
                              void*    stream_handler);

SRSLTE_API void srslte_ue_mib_sync_free(srslte_ue_mib_sync_t *q);

SRSLTE_API int srslte_ue_mib_sync_set_cell(srslte_ue_mib_sync_t* q, srslte_cell_t cell);

SRSLTE_API void srslte_ue_mib_sync_reset(srslte_ue_mib_sync_t * q); 

SRSLTE_API int srslte_ue_mib_sync_decode(srslte_ue_mib_sync_t * q, 
                                         uint32_t max_frames_timeout,
                                         uint8_t bch_payload[SRSLTE_BCH_PAYLOAD_LEN], 
                                         uint32_t *nof_tx_ports, 
                                         int *sfn_offset); 




#endif // SRSLTE_UE_MIB_H

