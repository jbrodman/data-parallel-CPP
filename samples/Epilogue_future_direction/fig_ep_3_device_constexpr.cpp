// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <sycl/sycl.hpp>

using namespace sycl;

int main() {
  queue q;

  q.submit([&](handler& h) {
     stream out(9, 9, h);
     h.parallel_for(range{1}, [=](id<1> idx) {
       if devconstexpr (this_device().has<aspect::cpu>()) {
         /* Code specialized for CPUs */
         out << "On a CPU!" << endl;
       } else if devconstexpr (this_device()
                                   .has<aspect::gpu>()) {
         /* Code specialized for GPUs */
         out << "On a GPU!" << endl;
       }
     });
   }).wait();
}
