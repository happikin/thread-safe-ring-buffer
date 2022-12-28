#include <iostream>
#include <thread>
#include <ring_buffer.hpp>

struct data_s {};

int main(int argc, char const *argv[]) {
    sdv::ring_buffer<data_s*,1'000'000> buffer;

    std::thread t1([&](){
        for(int i{};i<500'000;i++) {
            data_s *d = new data_s;
            buffer.push(d);
            d = nullptr;
        }
    });

    std::thread t2([&](){
        for(int i{};i<500'000;i++) {
            data_s *d = new data_s;
            buffer.push(d);
            d = nullptr;
        }
    });

    std::thread t3([&](){
        for(int i{};i<500'000;i++) {
            data_s *d = new data_s;
            buffer.push(d);
            d = nullptr;
        }
    });

    std::thread t4([&](){
        for(int i{};i<500'000;i++) {
            data_s *d = new data_s;
            buffer.push(d);
            d = nullptr;
        }
    });

    t1.join(); t2.join(); t3.join(); t4.join();
    std::cout << "received packets  : " << buffer.size() << "\n";
    std::cout << "lost packets      : " << buffer.lost_packets << "\n";
    
    return 0;
}