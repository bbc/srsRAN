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

#include "srsenb/hdr/metrics_csv.h"

#include <float.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

using namespace std;

namespace srsenb {

metrics_csv::metrics_csv(std::string filename) : n_reports(0), metrics_report_period(1.0), enb(NULL)
{
  file.open(filename.c_str(), std::ios_base::out);
}

metrics_csv::~metrics_csv()
{
  stop();
}

void metrics_csv::set_handle(enb_metrics_interface* enb_)
{
  enb = enb_;
}

void metrics_csv::stop()
{
  if (file.is_open()) {
    file << "#eof\n";
    file.flush();
    file.close();
  }
}

void metrics_csv::set_metrics(const enb_metrics_t& metrics, const uint32_t period_usec)
{
  if (file.is_open() && enb != NULL) {
    if (n_reports == 0) {
      file << "time;nof_ue;dl_brate;ul_brate\n";
    }

    // Time
    file << (metrics_report_period * n_reports) << ";";

    // UEs
    file << (metrics.stack.rrc.ues.size()) << ";";

    // Sum up rates for all UEs
    float dl_rate_sum = 0.0, ul_rate_sum = 0.0;
    for (size_t i = 0; i < metrics.stack.rrc.ues.size(); i++) {
      dl_rate_sum += metrics.stack.mac[i].tx_brate / (metrics.stack.mac[i].nof_tti * 1e-3);
      ul_rate_sum += metrics.stack.mac[i].rx_brate / (metrics.stack.mac[i].nof_tti * 1e-3);
    }

    // DL rate
    if (dl_rate_sum > 0) {
      file << float_to_string(SRSLTE_MAX(0.1, (float)dl_rate_sum), 2);
    } else {
      file << float_to_string(0, 2);
    }

    // UL rate
    if (ul_rate_sum > 0) {
      file << float_to_string(SRSLTE_MAX(0.1, (float)ul_rate_sum), 2, false);
    } else {
      file << float_to_string(0, 2, false);
    }

    file << "\n";

    n_reports++;
  } else {
    std::cout << "Error, couldn't write CSV file." << std::endl;
  }
}

std::string metrics_csv::float_to_string(float f, int digits, bool add_semicolon)
{
  std::ostringstream os;
  const int          precision = (f == 0.0) ? digits - 1 : digits - log10f(fabs(f)) - 2 * DBL_EPSILON;
  os << std::fixed << std::setprecision(precision) << f;
  if (add_semicolon)
    os << ';';
  return os.str();
}

} // namespace srsenb
