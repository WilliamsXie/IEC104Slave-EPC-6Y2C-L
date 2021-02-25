/*
 * configure.h
 *
 *  Created on: 2021-2-25
 *      Author: mr
 */

#ifndef CONFIGURE_HPP_
#define CONFIGURE_HPP_

#include <queue>
#include <list>
#include <map>

#include <string>
#include <time.h>

typedef struct 
{
    std::string version;
    bool debug_enabled;
    struct 
    {
        std::string filepath;   // configure file path
    } log4cplus;
    struct 
    {
        std::string host;
        int port;
        std::string password;
        struct timeval timeout;

        std::string up_channel;
        std::string down_channel;
    } redis;

    struct 
    {
        int port;
        int ca;
    } iec104;

    struct 
    {
        std::string filepath;
        std::string iec104slave_point_tb;
        std::string iec104master_tb;
    } sqlite3;

} IEC104ConfigST;

bool ConfigureLoad(std::string filepath, IEC104ConfigST &config);

#endif /* CONFIGURE_H_ */
