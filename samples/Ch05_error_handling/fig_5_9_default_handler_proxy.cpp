// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <sycl/sycl.hpp>
using namespace sycl;

// BEGIN CODE SNIP

// Our simple asynchronous handler function
auto handle_async_error = [](exception_list elist) {
  for (auto& e : elist) {
    try {
      std::rethrow_exception(e);
    } catch (sycl::exception& e) {
      // Print information about the asynchronous exception
    } catch (...) {
      // Print information about non-sycl::exception
    }
  }

  // Terminate abnormally to make clear to user that
  // something unhandled happened
  std::terminate();
};

// END CODE SNIP

void say_device(const queue& q) {
  std::cout << "Device : "
            << q.get_device().get_info<info::device::name>()
            << "\n";
}

class something_went_wrong {};

int main() {
  queue q{cpu_selector_v, handle_async_error};
  say_device(q);

  q.submit([&](handler& h) {
     h.host_task([]() { throw(something_went_wrong{}); });
   }).wait();

  return 0;
}
