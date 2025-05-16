# Multi-threaded Element Queue

This project implements a thread-safe, bounded queue template in C++ supporting primitive types. The queue uses dynamic memory allocation and synchronization primitives (`mutex`, `condition_variable`) to allow multiple threads to safely push and pop elements with optional timeout support.

## Features

- Fixed maximum capacity specified at construction.
- FIFO order with circular buffer.
- Thread-safe push and pop operations.
- Blocking behavior with optional timeout throwing exceptions on expiration.
- Implemented as a template for any primitive type.
- Unit tests included using Google Test.
- Build system with CMake supporting easy compilation and testing.

## Usage

- The example in `main.cpp` demonstrates concurrent producer and consumer threads interacting with the queue.
- Tests can be run with `ctest` or directly executing the test binary.

## Building

Requires C++17 compiler and CMake. Google Test is automatically downloaded via CMake's FetchContent.

```bash
mkdir build
cd build
cmake ..
cmake --build .
ctest

## Building and Running (Windows CMD)

### Required Tools (via [MSYS2](https://www.msys2.org/))

Install these from the MSYS2 UCRT64 terminal:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-toolchain
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-make

```bash
cd path\to\MultitheadQueueWithGTest
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
main.exe
QueueTest.exe

