#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//=========================================================

#include "../../include/logs/logs.hpp"
#include "../../include/logs/errors.h"

//=========================================================

static FILE* Logs_file = NULL;

//=========================================================

void dummy_func(void) {

    return;
}

//=========================================================

int _error_report(int error_code, const char* ___func_name, const char* ___file_name, int ___line) 
{

    fprintf(stderr, "\n ACHTUNG!!\n");

    fprintf(stderr, "\nAn error occured, my condolences((\n\n");

    fprintf(stderr, "File: %s\n", ___file_name);
    fprintf(stderr, "Function: %s\n", ___func_name);
    fprintf(stderr, "Line: %d\n", ___line);

    fprintf(stderr, "%s\n\n", get_error_descr(error_code));

    fflush(stderr);

    #ifdef LOGS

        fprintf(stderr, "This message also reported in log file,"
                        " see logs to get more information about"
                                        " programm performing\n");

        fprintf(Logs_file, "\n\n<div style = \" font-size: 15;"
                                            " text-align: center;"
                                            " color: white;"
                                            " background-color: red;\"><pre>\n");

        fprintf(Logs_file, "\nACHTUNG!!\n");

        fprintf(Logs_file, "\nAn error occured, my condolences((\n\n");

        fprintf(Logs_file, "File: %s\n", ___file_name);
        fprintf(Logs_file, "Function: %s\n", ___func_name);
        fprintf(Logs_file, "Line: %d\n\n", ___line);

        fprintf(Logs_file, "%s\n\n", get_error_descr(error_code));

        fprintf(Logs_file, "\n</pre></div>\n");

        fflush(Logs_file);

    #endif

    return 0;
}

//===================================================

void open_log_file(const char* filename) {

    if (filename == NULL)
    {
        printf("\n Incorrect log file name.\n");
        return;
    }

    char directory_name[DIR_NAME_SIZE];
    sprintf(directory_name, "%s%s", LOG_DIR, filename);

    Logs_file = fopen(directory_name, "wb");

    if (Logs_file == NULL) {

        fprintf(stderr, "Could not open log file\n");
        return;
    }

    write_head_html(Logs_file); 
    return;
}

//===================================================

void write_head_html(FILE* logs_file) {

    if (logs_file == NULL)
        return;

    fprintf(logs_file, "<html><head>");

    fprintf(logs_file, "<style>\n .outline {\n border: 0px solid black;"
                                           "\n padding: 0 10px;"
                                           "\n bgcolor = \"#196fA1\";"
                                           "\n color = \"white\";"
                                           "\n}\n </style>");

    fprintf(logs_file, "<style>\n .table { \n background: lightgrey;"
                                          "\n padding: 5px; border: 1px solid black;"
                                          "\n}\n</style>");
                                          
    fprintf(logs_file, "<style> \n td {\n border: 1px solid black;\n}\n </style>");
    
    fprintf(logs_file, "</head>");
    fprintf(logs_file, "\n<body bgcolor = \"#777777\">");


    return;
}

//===================================================

void close_log_file() {

    if (Logs_file == NULL)
        return;
    else
        fprintf(Logs_file, "</body></html>");

    int fclose_ret = fclose(Logs_file);

    if (fclose_ret == EOF)
    {
        fprintf(stderr, "Could not close log file\n");
        return;
    }

    Logs_file = NULL;

    return;
}

//================================================

int log_report_parameters_check(LOG_PARAMS) {

    if (my___line <= 0 
    ||  my___file_name == NULL 
    ||  my___func_name == NULL) {
    
        error_report(LOG_REPORT_PARAMS_ERR);
        return 0;
    }
    return 1;
}

//================================================

void _log_report(LOG_PARAMS, const char* mother_func) {

    if (log_report_parameters_check(LOGS_ARGS_USE) == 0)
        return;

    if (!Logs_file)
        return;

    fprintf(Logs_file, "\n<pre>\n");

    fprintf(Logs_file, "<div class=\"outline\"  "
                            "style = \"background-color:lightgrey;\" "
                            "style = \"text-align: center;\"><b>Funtion: %s\n\n</b> "
                            "Called from: function: <b>%s</b>, file: <b>%s</b>."
                            "Current line: <b>%d</b>.\n </div>", mother_func, 
                                        my___func_name, my___file_name, my___line);

    fprintf(Logs_file, "\n</pre>\n");
    fflush(Logs_file);

    return;
}

//================================================

void _smpl_log_report(LOG_PARAMS) {

    if (log_report_parameters_check(LOGS_ARGS_USE) == 0)
        return;

    if (!Logs_file)
        return;

    fprintf(Logs_file, "\n<pre>\n");

    fprintf(Logs_file, "<div class=\"outline\"  "
                            "style = \"background-color:lightgrey;\" "
                            "style = \"text-align: center;\"><b>Funtion: %s\n\n</b> "
                            "File: <b>%s</b>. Current line: <b>%d</b>.\n </div>",
                            my___func_name, my___file_name, my___line);
    fprintf(Logs_file, "\n</pre>\n");

    return;
}

//=================================================

#define DEF_ERR(code, name, string)                 \
                                                    \
    case code : {                                   \
                                                    \
        return #string;                             \
                                                    \
        break;                                      \
    }                                               \

//=================================================

const char* get_error_descr(int error_code) {

    switch (error_code) {

    #include "../../codegen/err_descr.txt"
    
    default:
        return NULL;
    }
}

#undef DEF_ERR

//=================================================
