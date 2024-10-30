#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
  std::cout << "\n";

  std::atomic<std::shared_ptr<std::string>> shared_string =
      std::make_shared<std::string>("Zero");

  // Capture the existing shared_ptr to use in lambdas
  auto existing_string = shared_string.load();

  std::thread t1([&shared_string, existing_string]() {
    existing_string->append("One");
    shared_string.store(existing_string);
  });

  std::thread t2([&shared_string, existing_string]() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    existing_string->append("Two");
    shared_string.store(existing_string);
  });

  std::thread t3([&shared_string, existing_string]() {
    existing_string->append("Three");
    shared_string.store(existing_string);
  });

  std::thread t4([&shared_string, existing_string]() {
    existing_string->append("Four");
    shared_string.store(existing_string);
  });

  std::thread t5([&shared_string, existing_string]() {
    existing_string->append("Five");
    shared_string.store(existing_string);
  });

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  std::cout << *shared_string.load() << std::endl;
  return 0;
}
