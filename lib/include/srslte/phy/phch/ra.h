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
 *  File:         ra.h
 *
 *  Description:  Implements Resource allocation Procedures common in for DL and UL
 *
 *  Reference:    3GPP TS 36.213 version 10.0.1 Release 10
 *****************************************************************************/

#ifndef SRSLTE_RA_H
#define SRSLTE_RA_H

#include <stdbool.h>
#include <stdint.h>

#include "srslte/config.h"
#include "srslte/phy/common/phy_common.h"

/**************************************************
 * Common structures used for Resource Allocation
 **************************************************/

typedef struct SRSLTE_API {
  srslte_mod_t mod;
  int          tbs;
  int          rv;
  uint32_t     nof_bits;
  uint32_t     cw_idx;
  bool         enabled;

  // this is for debugging and metrics purposes
  uint32_t mcs_idx;
} srslte_ra_tb_t;

typedef enum SRSLTE_API {
  SRSLTE_RA_ALLOC_TYPE0 = 0,
  SRSLTE_RA_ALLOC_TYPE1 = 1,
  SRSLTE_RA_ALLOC_TYPE2 = 2
} srslte_ra_type_t;

typedef struct SRSLTE_API {
  uint32_t rbg_bitmask;
} srslte_ra_type0_t;

typedef struct SRSLTE_API {
  uint32_t vrb_bitmask;
  uint32_t rbg_subset;
  bool     shift;
} srslte_ra_type1_t;

typedef struct SRSLTE_API {
  uint32_t riv; // if L_crb==0, DCI message packer will take this value directly
  enum { SRSLTE_RA_TYPE2_NPRB1A_2 = 0, SRSLTE_RA_TYPE2_NPRB1A_3 = 1 } n_prb1a;
  enum { SRSLTE_RA_TYPE2_NG1 = 0, SRSLTE_RA_TYPE2_NG2 = 1 } n_gap;
  enum { SRSLTE_RA_TYPE2_LOC = 0, SRSLTE_RA_TYPE2_DIST = 1 } mode;
} srslte_ra_type2_t;

#define SRSLTE_RA_NOF_TBS_IDX 34

SRSLTE_API uint32_t srslte_ra_type0_P(uint32_t nof_prb);

SRSLTE_API uint32_t srslte_ra_type2_n_vrb_dl(uint32_t nof_prb, bool ngap_is_1);

SRSLTE_API uint32_t srslte_ra_type2_n_rb_step(uint32_t nof_prb);

SRSLTE_API uint32_t srslte_ra_type2_ngap(uint32_t nof_prb, bool ngap_is_1);

SRSLTE_API uint32_t srslte_ra_type1_N_rb(uint32_t nof_prb);

SRSLTE_API uint32_t srslte_ra_type2_to_riv(uint32_t L_crb, uint32_t RB_start, uint32_t nof_prb);

SRSLTE_API void
srslte_ra_type2_from_riv(uint32_t riv, uint32_t* L_crb, uint32_t* RB_start, uint32_t nof_prb, uint32_t nof_vrb);

SRSLTE_API int srslte_ra_tbs_idx_from_mcs(uint32_t mcs, bool use_tbs_index_alt, bool is_ul);

SRSLTE_API srslte_mod_t srslte_ra_dl_mod_from_mcs(uint32_t mcs, bool use_tbs_index_alt);

SRSLTE_API srslte_mod_t srslte_ra_ul_mod_from_mcs(uint32_t mcs);

SRSLTE_API int srslte_ra_mcs_from_tbs_idx(uint32_t tbs_idx, bool use_tbs_index_alt, bool is_ul);

SRSLTE_API int srslte_ra_tbs_from_idx(uint32_t tbs_idx, uint32_t n_prb);

SRSLTE_API int srslte_ra_tbs_to_table_idx(uint32_t tbs, uint32_t n_prb);

#endif // SRSLTE_RA_H
