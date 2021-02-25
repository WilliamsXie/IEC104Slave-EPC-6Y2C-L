#ifndef __MY_LOG_HPP
#define __MY_LOG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <unistd.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/sleep.h>
#include <log4cplus/helpers/fileinfo.h>
#include <log4cplus/loggingmacros.h>

#define MY_LOG_CACHE_MAXSIZE								4096

#define MY_LOG_CONSOLE_FLAG								0x10
#define MY_LOG_ROLLFILE_FLAE								0x02
#define MY_LOG_MUTEX_ENABLE_FLAG						0x04

#define MY_LOG_CONSOLE_NAME						"console"
#define MY_LOG_ROLLFILE_NAME						"rollfile"
#define MY_LOG_WP_ROLLFILE_NAME					"rollfile.wp"
#define MY_LOG_SECUREACCESS_ROLLFILE_NAME		"rollfile.secure"
#define MY_LOG_POWER_ROLLFILE_NAME				"rollfile.power"

#define MY_ARRAY_LOG_FULL					0

#if MY_ARRAY_LOG_FULL
#else
	#define MY_ARRAY_LOG_START_LEN	42
	#define MY_ARRAY_LOG_END_LEN		42
#endif
using namespace std;
struct log_core
{
	unsigned char flag;
	char* cache_ptr;
	log4cplus::Logger rollfile;
	pthread_mutex_t mutex;
};

bool log_core_init(const char* conf);
struct log_core* log_core_create(const char* rollfile_name);
void log_core_destroy(struct log_core* ptr);
void log_core_lock(struct log_core* ptr);
void log_core_unlock(struct log_core* ptr);
void log_core_out(struct log_core* ptr,char *format, ...);
void log_core_array_out(struct log_core* ptr,unsigned char* buff_ptr,unsigned short len,char *format, ...);

/*#define LOG_TRACE(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_TRACE(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_TRACE(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_DEBUG(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_DEBUG(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_DEBUG(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_INFO(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_INFO(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_INFO(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_WARN(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_WARN(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_WARN(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ERROR(_ptr,_msg, _args...)	{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_ERROR(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_ERROR(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);sleep(1);exit(-1);}

#define LOG_ARRAY_TRACE(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_TRACE(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_TRACE(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_DEBUG(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_DEBUG(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_DEBUG(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_INFO(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_INFO(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_INFO(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_WARN(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_WARN(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_WARN(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_ERROR(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_CONSOLE_FLAG){LOG4CPLUS_ERROR(_ptr->console, _logstream.str());}if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_ERROR(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);sleep(1);exit(-1);}
*/

#define LOG_TRACE(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_TRACE(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_DEBUG(_ptr,_msg, _args...)	{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_DEBUG(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_INFO(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_INFO(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_WARN(_ptr,_msg, _args...)		{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_WARN(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ERROR(_ptr,_msg, _args...)	{stringstream _logstream;log_core_lock(_ptr);log_core_out(_ptr,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_ERROR(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}//sleep(1);exit(-1);}

#define LOG_ARRAY_TRACE(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_TRACE(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_DEBUG(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_DEBUG(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_INFO(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_INFO(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_WARN(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_WARN(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);}
#define LOG_ARRAY_ERROR(_ptr, _array_ptr,_array_len,_msg, _args...)		{std::stringstream _logstream;log_core_lock(_ptr);log_core_array_out(_ptr,(unsigned char*)_array_ptr,_array_len,_msg, ##_args);_logstream << _ptr->cache_ptr;if(_ptr->flag & MY_LOG_ROLLFILE_FLAE){LOG4CPLUS_ERROR(_ptr->rollfile, _logstream.str());}log_core_unlock(_ptr);sleep(1);exit(-1);}

#endif	//	#ifndef __MY_LOG_HPP
