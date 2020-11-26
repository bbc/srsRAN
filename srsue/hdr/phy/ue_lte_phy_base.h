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
 * File:        ue_lte_phy_base.h
 * Description: Base class for UE LTE PHYs.
 *****************************************************************************/

#ifndef SRSUE_UE_LTE_PHY_BASE_H
#define SRSUE_UE_LTE_PHY_BASE_H

#include "srslte/common/log_filter.h"
#include "srslte/interfaces/radio_interfaces.h"
#include "srsue/hdr/phy/ue_phy_base.h"

namespace srsue {

class ue_lte_phy_base : public ue_phy_base, public phy_interface_stack_lte, public srslte::phy_interface_radio
{
public:
  ue_lte_phy_base(){};
  virtual ~ue_lte_phy_base(){};

  virtual std::string get_type() = 0;

  virtual int  init(const phy_args_t& args_)                                                                       = 0;
  virtual int  init(const phy_args_t& args_, stack_interface_phy_lte* stack_, srslte::radio_interface_phy* radio_) = 0;
  virtual void stop()                                                                                              = 0;

  virtual void wait_initialize() = 0;
  virtual void start_plot()      = 0;

  virtual void get_metrics(phy_metrics_t* m) = 0;
};

} // namespace srsue

#endif // SRSUE_UE_LTE_PHY_BASE_H
