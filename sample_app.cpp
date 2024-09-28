#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string>
#include <csignal> 
#include "sample_app.hpp"

// Constructor opns the fifo to write
SampleApp::SampleApp() : fifoFd(-1), isRunning(true) {
    fifoFd = open("/tmp/watchdog_fifo", O_WRONLY | O_NONBLOCK);
    if (fifoFd < 0) {
        std::cerr << "Error opening FIFO: /tmp/watchdog_fifo" << std::endl;
        isRunning = false;
    }
}

// Destructor closes the fifo
SampleApp::~SampleApp() {
    if (fifoFd >= 0) {
        close(fifoFd);
    }
    isRunning = false;
}

// Function to start the application
void SampleApp::start() {
    if (!isRunning) return;

    std::cout << "Sample app started with PID: " << getpid() << std::endl;  // get the PID (Process ID) of the app
    std::cout.flush();

    while (isRunning) {
        sendHeartbeat();  // send a heartbeat
        std::cout << "Heartbeat sent by PID: " << getpid() << std::endl;
        std::cout.flush();
        sleep(10); // Sleep for 10 seconds before sending the next heartbeat
    }

    std::cout << "Sample app with PID: " << getpid() << " stopped\n";
}


// Fuction to send a heartbeat message to the Watchdog
void SampleApp::sendHeartbeat() {
    if (fifoFd < 0) return;

    std::string message = "Heartbeat from PID: " + std::to_string(getpid()) + "\n";  // create the heartbeat message
    ssize_t success = write(fifoFd, message.c_str(), message.size());  // write the message to the fifo
    if (success < 0) {
        std::cerr << "Error writing to FIFO" << std::endl;
    }
}

// Function to stop the app
void SampleApp::stop() {
    isRunning = false;
}
