// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

class Add;

int main() {
  constexpr size_t size = 16;
  std::array<int, size> data;

  for (int i = 0; i < size; i++) {
    data[i] = i;
  }

  {
    buffer data_buf{data};

    queue Q;
    std::cout
        << "Running on device: "
        << Q.get_device().get_info<info::device::name>()
        << "\n";

    Q.submit([&](handler& h) {
      accessor data_acc{data_buf, h};

      // BEGIN CODE SNIP
      // In this example, "class Add" names the kernel
      // lambda expression.
      h.parallel_for<class Add>(size, [=](id<1> i) {
        data_acc[i] = data_acc[i] + 1;
      });
      // END CODE SNIP
    });
  }

  for (int i = 0; i < size; i++) {
    if (data[i] != i + 1) {
      std::cout << "Results did not validate at index " << i
                << "!\n";
      return -1;
    }
  }

  std::cout << "Success!\n";
  return 0;
}
