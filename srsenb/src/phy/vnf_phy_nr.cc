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

#include <pthread.h>
#include <sstream>
#include <string.h>
#include <string>
#include <strings.h>
#include <sys/mman.h>
#include <unistd.h>

#include "srsenb/hdr/phy/vnf_phy_nr.h"
#include "srslte/common/basic_vnf_api.h"
#include "srslte/common/log.h"
#include "srslte/common/test_common.h"
#include "srslte/common/threads.h"

using namespace std;

namespace srsenb {

vnf_phy_nr::vnf_phy_nr(srslte::logger* logger_) : logger(logger_) {}

vnf_phy_nr::~vnf_phy_nr()
{
  stop();
}

void vnf_phy_nr::parse_config(const nr_phy_cfg_t& cfg) {}

int vnf_phy_nr::init(const srsenb::phy_args_t& args, const nr_phy_cfg_t& cfg, srsenb::stack_interface_phy_nr* stack_)
{
  mlockall(MCL_CURRENT | MCL_FUTURE);

  // create VNF
  vnf = std::unique_ptr<srslte::srslte_basic_vnf>(new srslte::srslte_basic_vnf(args.vnf_args, logger, stack_));

  initialized = true;

  return SRSLTE_SUCCESS;
}

void vnf_phy_nr::stop()
{
  if (initialized) {
    vnf->stop();
    initialized = false;
  }
}

// Start GUI
void vnf_phy_nr::start_plot() {}

void vnf_phy_nr::get_metrics(std::vector<srsenb::phy_metrics_t>& metrics) {}

int vnf_phy_nr::dl_config_request(const dl_config_request_t& request)
{
  // prepare DL config request over basic API and send
  return vnf->dl_config_request(request);
}

int vnf_phy_nr::tx_request(const tx_request_t& request)
{
  // send Tx request over basic API
  return vnf->tx_request(request);
}

} // namespace srsenb