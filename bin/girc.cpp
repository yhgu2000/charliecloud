#include <sched.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

extern "C"
{
#include "ch_core.h"
#include "config.h"
} // extern "C"

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace {

fs::path
current_executable()
{
  std::string buf(1024, '\0');
  auto len = readlink("/proc/self/exe", buf.data(), buf.size());
  if (len == -1)
    return {};
  buf.resize(len);
  return { buf };
}

} // namespace

extern "C" void
girc(const char* arg0, container* c)
{
  std::cout << "==================================================\n";
  std::cout << "newroot: " << c->newroot << '\n';
  std::cout << "img_ref: " << c->img_ref << '\n';
  std::cout << std::endl;

  fs::path newroot(c->newroot);
  auto dockerfiles = newroot / "Dockerfiles";
  if (!fs::exists(dockerfiles)) {
    std::cout << "Dockerfiles does not exist\n";
    return;
  }

  auto chimage = fs::weakly_canonical(current_executable() / ".." / "ch-image");
  if (!fs::exists(chimage)) {
    std::cout << "ch-image does not exist: " << chimage << "\n";
    return;
  }

  auto cmd = chimage.generic_string() + " build " +
             dockerfiles.generic_string() + " -t girc-test";
  auto out = popen(cmd.c_str(), "r");
  if (!out) {
    std::cout << "popen failed\n";
    return;
  }

  // print the output of the command
  char buf[1024];
  int n;
  while ((n = fread(buf, 1, sizeof(buf), out)) > 0) {
    fwrite(buf, 1, n, stdout);
  }
  auto retcode = pclose(out);
  if (retcode != 0) {
    std::cout << "ch-image build failed\n";
    return;
  }

  std::cout << "==================================================\n";
}
