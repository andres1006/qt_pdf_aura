// Logger.cpp
// Implementation of a multithread safe singleton logger class
#include <stdexcept>
#include "logger.h"
#include <ctime>
#include <cstdio>


using namespace std;

const string Logger::kLogLevelDebug = "DEBUG";
const string Logger::kLogLevelInfo = "INFO";
const string Logger::kLogLevelError = "ERROR";

const char* const Logger::kLogFileName = "log.out";

Logger* Logger::pInstance = nullptr;

mutex Logger::sMutex;

Logger& Logger::instance()
{
    static Cleanup cleanup;

    lock_guard<mutex> guard(sMutex);
    if (pInstance == nullptr)
        pInstance = new Logger();
    return *pInstance;
}

Logger::Cleanup::~Cleanup()
{
    lock_guard<mutex> guard(Logger::sMutex);
    delete Logger::pInstance;
    Logger::pInstance = nullptr;
}

Logger::~Logger()
{
    mOutputStream.close();
}

Logger::Logger()
{
    if (std::ifstream(kLogFileName))
    {
         remove(kLogFileName);
    }

    mOutputStream.open(kLogFileName, ios_base::app);
    if (!mOutputStream.good()) {
        throw runtime_error("Unable to initialize the Logger!");
    }
}

void Logger::log(const string& inMessage, const string& inLogLevel)
{
    lock_guard<mutex> guard(sMutex);
    logHelper(inMessage, inLogLevel);
}

void Logger::log(const vector<string>& inMessages, const string& inLogLevel)
{
    lock_guard<mutex> guard(sMutex);
    for (size_t i = 0; i < inMessages.size(); i++) {
        logHelper(inMessages[i], inLogLevel);
    }
}

void Logger::logHelper(const std::string& inMessage, const std::string& inLogLevel)
{
    time_t rawtime;
    char buffer[80];
    struct tm * timeinfo;


    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);
    mOutputStream << str << "   " <<inLogLevel << ": "<< inMessage << endl;
//    qDebug() << QString::fromStdString(str) << "   " <<QString::fromStdString(inLogLevel) << ": "<< QString::fromStdString(inMessage) << endl;
}
