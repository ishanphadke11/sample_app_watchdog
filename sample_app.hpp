#include <iostream>

// class for a sample application which simply writes heartbeats to the fifo opened by the Watchdog 
class SampleApp {
public:
    SampleApp();  // constructor
    ~SampleApp();  // destructor
    void start();  // function to start the app
    void stop();  // funcion to stop the app

private:
    void sendHeartbeat();  // private function to send a heartbeat
    int fifoFd;  // fifo file descriptor
    bool isRunning;  // variable keeps track f the apps running status
};