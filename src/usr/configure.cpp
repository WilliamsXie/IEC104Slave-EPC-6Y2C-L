/*
 * configure.cpp
 *
 *  Created on: 2021-2-25
 *      Author: mr
 */

#include "configure.h"

#include "tinyxml2/tinyxml2.h"

static bool _ConfigureLoadFromXML(std::string filepath, IEC104ConfigST &config)
{
    bool                   retval = false;
    tinyxml2::XMLError     err;
    tinyxml2::XMLDocument  doc;
    tinyxml2::XMLElement  *element[4];


    err = doc.LoadFile(filepath.c_str());
    if(err != tinyxml2::XML_SUCCESS)
    {
        printf("XML file<%s> Load Err<%d>\r\n", filepath.c_str(), err);
        goto return_flag;
    }

    element[0] = doc.RootElement();
    if(element[0] == NULL)
    {
        goto return_flag;
    }
    else
    {
        //printf("root element:%s\r\n", element[0]->Name());
        element[1] = element[0]->FirstChildElement("version");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            config.version = element[1]->GetText();
            printf("version:%s\r\n", config.version.c_str());
        }

        element[1] = element[0]->FirstChildElement("debug_enabled");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            config.debug_enabled = element[1]->BoolText();
            printf("debug_enabled:%d\r\n", config.debug_enabled);
        }

        element[1] = element[0]->FirstChildElement("log4cplus");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            element[2] = element[1]->FirstChildElement("filepath");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.log4cplus.filepath = element[2]->GetText();
                printf("config.log4cplus.filepath:%s\r\n", config.log4cplus.filepath.c_str());
            }
        }

        element[1] = element[0]->FirstChildElement("redis");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            element[2] = element[1]->FirstChildElement("host");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.redis.host = element[2]->GetText();
                printf("config.redis.host:%s\r\n", config.redis.host.c_str());
            }

            element[2] = element[1]->FirstChildElement("port");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.redis.port = element[2]->IntText();
                printf("config.redis.port:%d\r\n", config.redis.port);
            }

            element[2] = element[1]->FirstChildElement("password");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.redis.password = element[2]->GetText();
                printf("config.redis.password:%s\r\n", config.redis.password.c_str());
            }

            element[2] = element[1]->FirstChildElement("timeout");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                element[3] = element[2]->FirstChildElement("sec");
                if(element[3] == NULL)
                {
                    goto return_flag;
                }
                else
                {
                    config.redis.timeout.tv_sec = element[3]->IntText();
                    printf("config.redis.timeout.tv_sec:%d\r\n", config.redis.timeout.tv_sec);
                }

                element[3] = element[2]->FirstChildElement("usec");
                if(element[3] == NULL)
                {
                    goto return_flag;
                }
                else
                {
                    config.redis.timeout.tv_usec = element[3]->IntText();
                    printf("config.redis.timeout.tv_usec:%d\r\n", config.redis.timeout.tv_usec);
                }
            }

            element[2] = element[1]->FirstChildElement("up_channel");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.redis.up_channel = element[2]->GetText();
                printf("config.redis.up_channel:%s\r\n", config.redis.up_channel.c_str());
            }

            element[2] = element[1]->FirstChildElement("down_channel");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.redis.down_channel = element[2]->GetText();
                printf("config.redis.down_channel:%s\r\n", config.redis.down_channel.c_str());
            }
        }

        element[1] = element[0]->FirstChildElement("iec104");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            element[2] = element[1]->FirstChildElement("port");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.iec104.port = element[2]->IntText();
                printf("config.iec104.port:%d\r\n", config.iec104.port);
            }

            element[2] = element[1]->FirstChildElement("ca");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.iec104.ca = element[2]->IntText();
                printf("config.iec104.ca:%d\r\n", config.iec104.ca);
            }
        }

        element[1] = element[0]->FirstChildElement("sqlite3");
        if(element[1] == NULL)
        {
            goto return_flag;
        }
        else
        {
            element[2] = element[1]->FirstChildElement("filepath");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.sqlite3.filepath = element[2]->GetText();
                printf("config.sqlite3.filepath:%s\r\n", config.sqlite3.filepath.c_str());
            }

            element[2] = element[1]->FirstChildElement("iec104slave_point_tb");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.sqlite3.iec104slave_point_tb = element[2]->GetText();
                printf("config.sqlite3.iec104slave_point_tb:%s\r\n", config.sqlite3.iec104slave_point_tb.c_str());
            }

            element[2] = element[1]->FirstChildElement("iec104master_tb");
            if(element[2] == NULL)
            {
                goto return_flag;
            }
            else
            {
                config.sqlite3.iec104master_tb = element[2]->GetText();
                printf("config.sqlite3.iec104master_tb:%s\r\n", config.sqlite3.iec104master_tb.c_str());
            }
        } 
    }
    retval = true;
return_flag:
    return (retval);
}

static bool _ConfigureLoadFromDB(std::string filepath, IEC104ConfigST &config)
{

}

bool ConfigureLoad(std::string filepath, IEC104ConfigST &config)
{
    bool retval = false;


    if(false == _ConfigureLoadFromXML(filepath, config))
    {
        printf("XML File Load Err\r\n");
        goto return_flag;
    }

    if(false == _ConfigureLoadFromDB(config.sqlite3.filepath, config))
    {
        printf("sqlite3 DB File Load Err\r\n");
        goto return_flag;
    }
    retval = true;
return_flag:
    return (retval);
}




