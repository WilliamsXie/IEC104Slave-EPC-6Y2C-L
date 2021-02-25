/*
 * main.cpp
 *
 *  Created on: 2021-2-25
 *      Author: mr
 */

#include "configure.hpp"

#include "iec104slave.hpp"

#include <stdio.h>



int main(int argc, char *argv[])
{
	//printf("hello\r\n");
	IEC104ConfigST conf;
	if(argc != 2)
	{
		printf("argument err\r\n");
		return (-1);
	}
	
	ConfigureLoad(argv[1], conf);

	return (0);
}


