/*
 * main.cpp
 *
 *  Created on: 2021-2-25
 *      Author: mr
 */

#include "iec104slave.hpp"
#include "configure.hpp"

#include <stdio.h>

IEC104SlaveST IEC104Slave;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("argument err\r\n");
		goto program_exit;
	}

	//load config
	if(false == ConfigureLoad(argv[1], IEC104Slave.config))
	{
		printf("Configure Load Failed\r\n");
		goto program_exit;
	}

	IEC104SlaveRun(&IEC104Slave);
	
program_exit:
	return (0);
}


