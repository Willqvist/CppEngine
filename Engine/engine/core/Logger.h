//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_LOGGER_H
#define CPPMC_LOGGER_H

#include <stdio.h>
#if defined DEBUG_ENABLE || defined DEBUG || defined _DEBUG || defined NDEBUG
#define DEBUG_LOG(...) fprintf(stdout,"[ENGINE - LOG] ");fprintf(stdout,__VA_ARGS__);fprintf(stdout,"\n");
#define DEBUG_ERROR(...) fprintf(stderr,"[ENGINE - ERROR] ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");
#else
#define DEBUG_LOG(...)
#define DEBUG_ERROR(...)
#endif
#endif //CPPMC_LOGGER_H
