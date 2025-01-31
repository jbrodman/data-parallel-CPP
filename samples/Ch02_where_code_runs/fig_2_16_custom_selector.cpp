// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

// START CODE SNIP

int my_selector(const device &dev) {
  if (dev.get_info<info::device::name>().find("pac_a10") !=
          std::string::npos &&
      dev.get_info<info::device::vendor>().find("Intel") !=
          std::string::npos) {
    return 1;
  }
  return -1;
}

// END CODE SNIP

int main() {
  queue q(my_selector);

  std::cout << "Selected device is: "
            << q.get_device().get_info<info::device::name>()
            << "\n";

  return 0;
}
