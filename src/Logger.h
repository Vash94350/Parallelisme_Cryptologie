//
// Created by PEAN Michael on 24/10/2018.
//

#ifndef PRODUCER_CONSUMER_Logger_H
#define PRODUCER_CONSUMER_Logger_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <string>

namespace producer_consumer
{
    namespace sequential
    {
        class Logger
        {
        public:
            void debug(std::string str)
            {
                std::cout << "DEBUG" << str << std::endl;
            }
            void info(std::string str)
            {
                std::cout << "INFO" << str << std::endl;
            }
            void warning(std::string str)
            {
                std::cout << "WARNING" << str << std::endl;
            }
            void error(std::string str)
            {
                std::cout << "ERROR" << str << std::endl;
            }
        private:
        };
    }
}   // sequential
#endif
