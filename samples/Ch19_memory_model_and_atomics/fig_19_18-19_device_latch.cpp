// Copyright (C) 2023 Intel Corporation

// SPDX-License-Identifier: MIT

#include <cassert>
#include <cstdio>
#include <sycl/sycl.hpp>

using namespace sycl;

struct device_latch {
  explicit device_latch(size_t num_groups)
      : counter(0), expected(num_groups) {}

  template <int Dimensions>
  void arrive_and_wait(nd_item<Dimensions>& it) {
    auto grp = it.get_group();
    group_barrier(grp);
    // Elect one work-item per work-group to be involved in
    // the synchronization All other work-items wait at the
    // barrier after the branch
    if (grp.leader()) {
      atomic_ref<size_t, memory_order::acq_rel,
                 memory_scope::device,
                 access::address_space::global_space>
          atomic_counter(counter);

      // Signal arrival at the barrier
      // Previous writes should be visible to all work-items
      // on the device
      atomic_counter++;

      // Wait for all work-groups to arrive
      // Synchronize with previous releases by all
      // work-items on the device
      while (atomic_counter.load() != expected) {
      }
    }
    group_barrier(grp);
  }

  size_t counter;
  size_t expected;
};

int main() {
  queue q;

  // The number of groups here must be chosen carefully to
  // guarantee forward progress!
  size_t num_groups = 8;
  size_t items_per_group = 64;
  nd_range<1> R = nd_range<1>(num_groups * items_per_group,
                              items_per_group);

  // Allocate two arrays in USM
  // The first will be used for communication
  // The second will be used for validation
  size_t* data = sycl::malloc_shared<size_t>(
      num_groups * items_per_group, q);
  size_t* sums = sycl::malloc_shared<size_t>(
      num_groups * items_per_group, q);

  // Allocate a one-time-use device_latch in USM
  void* ptr = sycl::malloc_shared(sizeof(device_latch), q);
  device_latch* latch = new (ptr) device_latch(num_groups);
  q.submit([&](handler& h) {
     h.parallel_for(R, [=](nd_item<1> it) {
       // Every work-item writes a 1 to its location
       data[it.get_global_linear_id()] = 1;

       // Every work-item waits for all writes
       latch->arrive_and_wait(it);

       // Every work-item sums the values it can see
       size_t sum = 0;
       for (int i = 0; i < num_groups * items_per_group;
            ++i) {
         sum += data[i];
       }
       sums[it.get_global_linear_id()] = sum;
     });
   }).wait();
  free(ptr, q);

  // Check that all work-items saw all writes
  bool passed = true;
  for (int i = 0; i < num_groups * items_per_group; ++i) {
    if (sums[i] != num_groups * items_per_group) {
      passed = false;
    }
  }
  std::cout << ((passed) ? "SUCCESS\n" : "FAILURE\n");

  free(sums, q);
  free(data, q);
  return (passed) ? 0 : 1;
}
