// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <sycl/sycl.hpp>
using namespace sycl;

int main() {
  try {
    buffer<int> b{range{16}};

    // ERROR: Create sub-buffer larger than size of parent
    // buffer An exception is thrown from within the buffer
    // constructor
    buffer<int> b2(b, id{8}, range{16});

  } catch (sycl::exception &e) {
    // Do something to output or handle the exception
    std::cout << "Caught synchronous SYCL exception: "
              << e.what() << "\n";
    return 1;
  } catch (std::exception &e) {
    std::cout << "Caught std exception: " << e.what()
              << "\n";
    return 2;
  } catch (...) {
    std::cout << "Caught unknown exception\n";
    return 3;
  }

  return 0;
}
