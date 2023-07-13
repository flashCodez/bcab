#include <CL/sycl.hpp>
#include <iostream>

using namespace sycl;

class helloSYCL;

int main() {
  // Create a SYCL queue to submit work to the device
  sycl::queue myQueue;

  // Submit a command group to the queue
  myQueue.submit([&](sycl::handler& cgh) {
    // Create an accessor to write the output
    sycl::stream output(1024, 256, cgh);

    // Execute the kernel
    cgh.single_task<class helloSYCL>([=]() {
      // Print "Hello, SYCL!" to the output stream
      output << "Hello, SYCL!" << sycl::endl;
    });
  });

  // Wait for the queue to finish
  myQueue.wait();

  return 0;
}
