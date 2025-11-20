#include <memory.h>

#include <iostream>
#include <memory>
#include <string>

#include "allocator.h"
#include "btree.h"
#include "client_logger_builder.h"
#include "logger_builder.h"

int main(int argc, char** argv) {
  auto log = std::shared_ptr<logger>(
      client_logger_builder()
          .transform_with_configuration(argv[1], argv[2])
          ->build());

  // auto alloc = std::shared_ptr<allocator>(new
  // allocator_global_heap(log.get()));
  auto alloc = std::shared_ptr<allocator>(nullptr);
  return 0;
}
