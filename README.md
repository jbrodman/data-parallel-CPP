# Data Parallel C++ Book Source Samples

This repository accompanies [*Data Parallel C++: Mastering DPC++ for Programming of Heterogeneous Systems using C++ and SYCL*](https://www.apress.com/9781484255735) by James Reinders, Ben Ashbaugh, James Brodman, Michael Kinsner, John Pennycook, Xinmin Tian (Apress, 2020).

[comment]: #cover
![Cover image](images/9781484255735.jpg)

## Purpose of this branch (main)

This branch (main) contains source code derived from what was published with the First Edition of the DPC++ book, but modified to be compatible with the SYCL 2020 specification which was released by The Khronos Group after book publication.  The original book source was primarily based on the older SYCL 1.2.1 specification, and many enhancements and changes were added in the later SYCL 2020 specification.  More importantly, most current toolchains which support SYCL are based on SYCL 2020, so this main branch is intended to be compatible with recent compiler and toolchain releases.

The Second Edition of the DPC++ book, likely to release in 2023, will be based on the updated code examples in this main branch.

## Overview

Many of the samples in the book are snips from the more complete files in this repository.  The full files contain supporting code, such as header inclusions, which are not shown in every listing within the book.  The complete listings are intended to compile and be modifiable for experimentation.

Samples in this repository are updated to align with the most recent changes to the language and
toolchains, and are more current than captured in the book text due to lag between finalization and actual
publication of a print book.  If experimenting with the code samples, start with the versions in this
repository.  DPC++ and SYCL are evolving to be more powerful and easier to use, and updates to the sample code
in this repository are a good sign of forward progress!

Download the files as a zip using the green button, or clone the repository to your machine using Git.

## How to Build the Samples

The samples in this repository are intended to compile with the open source project toolchain linked below, or
with the 2023.0 release or newer of the DPC++ toolchain.  If you have an older toolchain installed, you may encounter
compilation errors due to evolution of the features and extensions.

### Prerequisites

1. An installed SYCL toolchain.  See below for details on the tested DPC++ toolchain
1. CMake 3.10 or newer (Linux) or CMake 3.25 or newer (Windows)
1. Ninja or Make - to use the build steps described below

To build and use these examples, you will need an installed DPC++ toolchain.  For one such toolchain, please visit:

https://software.intel.com/content/www/us/en/develop/tools/oneapi/components/dpc-compiler.html

Alternatively, much of the toolchain can be built directly from:

https://github.com/intel/llvm

Some of the samples require other dependencies.  To disable samples requiring these dependencies use the CMake variables described below.

### Setting Up an Environment to Build the Samples

Setup environment variables if using a oneAPI / DPC++ implementation:

On Windows:

```sh
\path\to\inteloneapi\setvars.bat
```

On Linux:

```sh
source /path/to/inteloneapi/setvars.sh
```

### Building the Samples:

> **Note**: 
> CMake supports different [generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) to create build files for different build systems.  Some popular generators are `Unix Makefiles` or `Ninja` when building from the command line, and `Visual Studio`-based generators when building from a Windows IDE.  The examples below generate build files for `Unix Makefiles`, but feel free to substitute a different generator, if preferred.

1. Create build files using CMake.  For example:

    ```sh
    mkdir build && cd build
    cmake -G "Unix Makefiles" ..
    ```

2. Build with the generated build files:

    ```sh
    cmake --build . --target install --parallel
    ```

    Or, use the generated Makefiles directly:

    ```sh
    make install -j8
    ```

If your SYCL compiler is not detected automatically, or to explicitly specify a different SYCL compiler, use the `CMAKE_CXX_COMPILER` variable.  For example:

```sh
cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/path/to/your/sycl/compiler ..
```

## CMake Variables:

The following CMake variables are supported.  To specify one of these variables
via the command line generator, use the CMake syntax `-D<option name>=<value>`.
See your CMake documentation for more details.

| Variable | Type | Description |
|:---------|:-----|:------------|
| NODPL | BOOL | Disable samples that require the oneAPI DPC++ Library (oneDPL).  Default: `FALSE`
| NODPCT | BOOL | Disable samples that require the DPC++ Compatibility Tool (dpct).  Default: `FALSE`
| NOL0 | BOOL | Disable samples that require the oneAPI Level Zero Headers and Loader.  Default: `TRUE`
| WITHCUDA | BOOL | Enable CUDA device support for the samples.  Default: `FALSE`
