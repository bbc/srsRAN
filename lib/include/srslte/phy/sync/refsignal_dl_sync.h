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

#ifndef SRSLTE_REFSIGNAL_DL_SYNC_H_
#define SRSLTE_REFSIGNAL_DL_SYNC_H_

#include <srslte/phy/ch_estimation/refsignal_dl.h>
#include <srslte/phy/dft/ofdm.h>
#include <srslte/phy/utils/convolution.h>

typedef struct {
  srslte_refsignal_t   refsignal;
  srslte_ofdm_t        ifft;
  cf_t*                ifft_buffer_in;
  cf_t*                ifft_buffer_out;
  cf_t*                sequences[SRSLTE_NOF_SF_X_FRAME];
  cf_t*                correlation;
  srslte_conv_fft_cc_t conv_fft_cc;

  // Results
  bool     found;
  float    rsrp_dBfs;
  float    rssi_dBfs;
  float    rsrq_dB;
  float    cfo_Hz;
  uint32_t peak_index;
} srslte_refsignal_dl_sync_t;

SRSLTE_API int srslte_refsignal_dl_sync_init(srslte_refsignal_dl_sync_t* q);

SRSLTE_API int srslte_refsignal_dl_sync_set_cell(srslte_refsignal_dl_sync_t* q, srslte_cell_t cell);

SRSLTE_API void srslte_refsignal_dl_sync_free(srslte_refsignal_dl_sync_t* q);

SRSLTE_API void srslte_refsignal_dl_sync_run(srslte_refsignal_dl_sync_t* q, cf_t* buffer, uint32_t nsamples);

SRSLTE_API void srslte_refsignal_dl_sync_measure_sf(srslte_refsignal_dl_sync_t* q,
                                                    cf_t*                       buffer,
                                                    uint32_t                    sf_idx,
                                                    float*                      rsrp,
                                                    float*                      rssi,
                                                    float*                      cfo);

#endif // SRSLTE_REFSIGNAL_DL_SYNC_H_
