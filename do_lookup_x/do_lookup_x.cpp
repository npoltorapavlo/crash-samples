#include <dlfcn.h>

#include <thread>
#include <mutex>

void *handle = nullptr;

std::mutex lock;

int main() {

    std::thread thread1([]() {
      while (true) {
        lock.lock();

        if (handle != nullptr) {
          printf("dlsym\n");
          fflush(stdout);

          void (*func)() = (void (*)()) dlsym(handle, "func");

          lock.unlock();

          func();

          printf("after func()\n");
          fflush(stdout);
        } else {
          lock.unlock();
        }
      }
    });

    std::thread thread2([]() {
      while (true) {
        lock.lock();

        if (handle != nullptr) {
          printf("dlclose\n");
          fflush(stdout);

          dlclose(handle);
          handle = nullptr;
        }

        lock.unlock();
      }
    });

    std::thread thread3([]() {
      while (true) {
        lock.lock();

        if (handle == nullptr) {
          printf("dlopen\n");
          fflush(stdout);

          handle = dlopen("./libdl1.so", RTLD_LAZY);
        }

        lock.unlock();
      }

    });

//  handle = dlopen("./libdl1.dylib", RTLD_LAZY);

    thread3.join();
    thread1.join();
    thread2.join();


//  void (*func)() = (void (*)())dlsym(handle, "func");
//  func();

//  dlclose(handle);
  return 0;
}
