/**
 * @brief this is the implementation of thread safe ring buffer with std::atomic_flag implementation
 * @version v0.0.1
 * @namespace sdv
*/

#include <atomic>
#include <mutex>
#include <stddef.h>
#include <iostream>
#include <thread>

namespace sdv {
    template <typename type, size_t buffersize>
    class ring_buffer {
        private:
            type* m_inner_data; // pointer to inner buffer
            size_t m_size; // will give actual number of entries
            size_t m_max_size; // will store the max size of this buffer
            size_t head, tail; // insertion will happen at head and pop at tail
            std::atomic_flag m_not_free;
            uint16_t m_sleep_time;

        public:
            size_t lost_packets;

        public:
            ring_buffer() : m_not_free(ATOMIC_FLAG_INIT), m_max_size(buffersize), m_sleep_time(5) {
                this->m_inner_data = new type[m_max_size];
                this->head = this->tail = 0;
                m_size = 0;
            }
            ~ring_buffer() {delete[] this->m_inner_data;}
            void push(type _dataitem) {
                while(this->m_not_free.test_and_set()) {
                    std::this_thread::sleep_for(std::chrono::microseconds(m_sleep_time));
                }
                if(!this->full()) {
                    this->m_inner_data[head] = _dataitem;
                    this->head = (this->head+1) % this->m_max_size;
                    this->m_size++;
                } else ++lost_packets;
                this->m_not_free.clear();
            }
            void pop(type& _outdata) {
                while(this->m_not_free.test_and_set()) {
                    std::this_thread::sleep_for(std::chrono::microseconds(m_sleep_time));
                }
                if(!this->empty()) {
                    _outdata = this->m_inner_data[tail];
                    this->tail = (this->tail+1) % this->m_max_size;
                    this->m_size--;
                } // else std::cout << "empty\n";
                this->m_not_free.clear();
            }
            size_t size() const { return this->m_size; }
            bool full() const { return this->m_size == this->m_max_size; }
            bool empty() const { return this->m_size == 0; }
    };
} // namespace logger
