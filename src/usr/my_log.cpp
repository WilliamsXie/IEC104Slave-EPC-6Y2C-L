#include "my_log.hpp"
#include "string.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

bool log_core_init(const char* conf)
{
	log4cplus::initialize ();
	LogLog::getLogLog()->setInternalDebugging(true);
	//Logger root = Logger::getRoot();
	ConfigureAndWatchThread configureThread(conf, 60);
	//LOG4CPLUS_INFO(root, "My Log Module Initing...");
	//LOG4CPLUS_INFO(root, "My Log Module Init Done");
}

struct log_core* log_core_create(const char* rollfile_name)
{
	struct log_core* ret = NULL;
	//Logger root = Logger::getRoot();
	ret = new struct log_core;
	ret->cache_ptr = (char*)malloc(MY_LOG_CACHE_MAXSIZE);
	if(ret->cache_ptr == NULL)
	{
		//LOG4CPLUS_ERROR(root, "MY LOG Create Cache Failed");
		delete(ret);
		ret = NULL;
		goto return_flag;
	}
	ret->flag = MY_LOG_ROLLFILE_FLAE | MY_LOG_MUTEX_ENABLE_FLAG;

	if(ret->flag & MY_LOG_ROLLFILE_FLAE)
	{
		ret->rollfile =  Logger::getInstance(LOG4CPLUS_TEXT(rollfile_name));
	}

	if(ret->flag & MY_LOG_MUTEX_ENABLE_FLAG)
	{
		pthread_mutex_init(&(ret->mutex),NULL);
	}
return_flag:
	 return ret;
}

void log_core_destroy(struct log_core* ptr)
{
	Logger root = Logger::getRoot();
	if(ptr != NULL)
	{
		if(ptr->flag & MY_LOG_MUTEX_ENABLE_FLAG)
		{
			pthread_mutex_destroy(&(ptr->mutex));
		}
		free(ptr->cache_ptr);
		ptr->cache_ptr = NULL;
		delete ptr;
	}
	LOG4CPLUS_INFO(root, "My Log Module Destroy Done");
}

void log_core_lock(struct log_core* ptr)
{
	if(ptr != NULL)
	{
		if(ptr->flag & MY_LOG_MUTEX_ENABLE_FLAG)
		{
			pthread_mutex_lock(&(ptr->mutex));
		}
	}
}
void log_core_unlock(struct log_core* ptr)
{
	if(ptr != NULL)
	{
		if(ptr->flag & MY_LOG_MUTEX_ENABLE_FLAG)
		{
			pthread_mutex_unlock(&(ptr->mutex));
		}
	}
}

void log_core_out(struct log_core* ptr,char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsnprintf(ptr->cache_ptr,MY_LOG_CACHE_MAXSIZE, format, ap);
	va_end(ap);
}

void log_core_array_out(struct log_core* ptr,unsigned char* buff_ptr,unsigned short len,char *format, ...)
{
	int i;
	va_list ap;
	va_start(ap, format);
	vsnprintf(ptr->cache_ptr,MY_LOG_CACHE_MAXSIZE, format, ap);
	snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"[LEN:%d] ",len);
#if	MY_ARRAY_LOG_FULL
		for(i = 0;i < len;++i)
		{
			if((MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr)) < 4)
			{
				break;
			}
			snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"%02x ",*(buff_ptr + i));
		}
		strcpy(ptr->cache_ptr + MY_LOG_CACHE_MAXSIZE - 4,"\r\n");
#else
		if(len <= (MY_ARRAY_LOG_START_LEN + MY_ARRAY_LOG_END_LEN))
		{
			for(i = 0;i < len;++i)
			{
				if((MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr)) < 4)
				{
					break;
				}
				snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"%02x ",*(buff_ptr + i));
			}
			strcpy(ptr->cache_ptr + MY_LOG_CACHE_MAXSIZE - 4,"\r\n");
		}
		else
		{
			for(i = 0;i < MY_ARRAY_LOG_START_LEN;++i)
			{
				snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"%02x ",*(buff_ptr + i));
			}
			snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"...... ");
			for(i = 0;i < MY_ARRAY_LOG_END_LEN;++i)
			{
				snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"%02x ",*(buff_ptr + len - MY_ARRAY_LOG_END_LEN + i));
			}
			//snprintf(ptr->cache_ptr + strlen(ptr->cache_ptr),MY_LOG_CACHE_MAXSIZE - strlen(ptr->cache_ptr),"\r\n");
		}
#endif	//	#if	MY_ARRAY_LOG_FULL
	va_end(ap);
}
