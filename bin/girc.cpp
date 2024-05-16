#include <sched.h>
#include <sys/stat.h>

extern "C"
{
#include "ch_core.h"
#include "config.h"
} // extern "C"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

extern "C" void
girc(container* c)
{
  std::cout << "==================================================\n";
  std::cout << "newroot: " << c->newroot << '\n';
  std::cout << "img_ref: " << c->img_ref << '\n';
  std::cout << "initial_dir: " << c->type << '\n';
  for (auto&& dir : fs::directory_iterator("/"))
    std::cout << dir.path() << '\n';
  std::cout << "==================================================\n";
}
