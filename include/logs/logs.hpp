#pragma once

//=========================================================

#include <stdio.h>

//=========================================================

#include "../../conf/global_conf.hpp"
#include "errors.h"

//=========================================================

#ifndef LOG_DIR

    #define LOG_DIR "/tmp/"

#endif

//=========================================================

#pragma once

#define LOG_PARAMS \
        const char* my___func_name, const char* my___file_name, int my___line

#define LOG_ARGS \
        __FUNCTION__, __FILE__, __LINE__

#define LOGS_ARGS_USE \
        my___func_name, my___file_name, my___line
;

//=========================================================

#define LOG_FILE_DIR_BUF_SIZE 100

#define DIR_NAME_SIZE 300

//===================================================================

#ifdef LOGS

    #define FOR_LOGS(...) __VA_ARGS__

#else

    #define FOR_LOGS(...)

#endif

//===================================================================

#ifdef LOGS

    #define log_report() \
           _log_report(LOGS_ARGS_USE, __FUNCTION__)

    #define smpl_log_report() \
	       _smpl_log_report(LOG_ARGS)

#else

    #define log_report() 

    #define smpl_log_report() 

#endif

#define error_report(err_code) \
       _error_report(err_code, LOG_ARGS)

//===================================================================

int _error_report(int error_code, const char* ___func_name, const char* ___file_name, int ___line);

//===================================================================

void dummy_func(void);

void open_log_file(const char* filename);

void write_head_html(FILE* logs_file);

void close_log_file();

void _log_report(LOG_PARAMS, const char* mother_func);

int log_report_parameters_check(LOG_PARAMS);

void _smpl_log_report(LOG_PARAMS);

const char* get_error_descr(int error_code);


