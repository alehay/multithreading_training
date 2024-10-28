#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

int main(int argc, char *argv[])
{
    std::cout << "\n";

    std::shared_ptr<std::string> shared_string = std::make_shared<std::string>("Zero");

    std::thread t1([&shared_string]()
                   {
        std::shared_ptr<std::string> local_string = std::atomic_load(&shared_string);
        *local_string += "One";
        std::atomic_store(&shared_string, local_string); });

    std::thread t2([&shared_string]()
                   {
        std::shared_ptr<std::string> local_string = std::atomic_load(&shared_string);
        *local_string += "Two";
        std::atomic_store(&shared_string, local_string); });

    std::thread t3([&shared_string]()
                   {
        std::shared_ptr<std::string> local_string = std::atomic_load(&shared_string);
        *local_string += "Three";
        std::atomic_store(&shared_string, local_string); });

    std::thread t4([&shared_string]()
                   {
        std::shared_ptr<std::string> local_string = std::atomic_load(&shared_string);
        *local_string += "Four";
        std::atomic_store(&shared_string, local_string); });

    std::thread t5([&shared_string]()
                   {
        std::shared_ptr<std::string> local_string = std::atomic_load(&shared_string);
        *local_string += "Five";
        std::atomic_store(&shared_string, local_string); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << *std::atomic_load(&shared_string) << std::endl;
    return 0;
}
