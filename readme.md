#### Overview
1.  This is a thread safe container based on ring buffer data structure
2.  Thread safety has been acheived using std::atomic_flag to simulate the use of a mutex
3.  Best part of the ring_buffer is its ability to take in size and type as template argument

#### How To Build
    mkdir build
    cmake ..
    make