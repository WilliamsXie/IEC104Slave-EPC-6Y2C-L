/*
 * iec104slave.hpp
 *
 *  Created on: 2021-2-25
 *      Author: mr
 */

#ifndef IEC104SLAVE_HPP_
#define IEC104SLAVE_HPP_

#include "configure.hpp"

typedef struct 
{
    IEC104ConfigST config;


} IEC104SlaveST;

void IEC104SlaveRun(IEC104SlaveST *handle);

#endif /* IEC104SLAVE_HPP_ */
