#include <iostream>
#include <memory>
#include <atomic>
#include <string>
#include <thread>

int main(int argc, char *argv[])
{
    std::cout << "\n";

    std::atomic<std::shared_ptr<std::string>> shared_string = std::make_shared<std::string>("Zero");

    std::thread t1([&shared_string]
                   { shared_string.store(std::make_shared<std::string>(*shared_string.load() + "One")); });

    std::thread t2([&shared_string]
                   { shared_string.store(std::make_shared<std::string>(*shared_string.load() + "Two")); });

    std::thread t3([&shared_string]()
                   { shared_string.store(std::make_shared<std::string>(*shared_string.load() + "Three")); });

    std::thread t4([&shared_string]()
                   { shared_string.store(std::make_shared<std::string>(*shared_string.load() + "Four")); });

    std::thread t5([&shared_string]()
                   { shared_string.store(std::make_shared<std::string>(*shared_string.load() + "Five")); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << *shared_string.load() << std::endl;
    return 0;
}