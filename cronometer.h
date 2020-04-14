#pragma once

#ifdef _WIN32
    #include <windows.h>

    typedef struct
    {
        LARGE_INTEGER init;
        LARGE_INTEGER end;
    } cronometer;

    #define CRONO_THIS(X)                                                                           \
    {                                                                                               \
        cronometer crono;                                                                           \
        LARGE_INTEGER freq;                                                                         \
        QueryPerformanceCounter(&crono.init);                                                       \
        X;                                                                                          \
        QueryPerformanceCounter(&crono.end);                                                        \
        QueryPerformanceFrequency(&freq);                                                           \
        printf(#X " in %.16g millisecs\n",                                                               \
            ((double)(crono.end.QuadPart - crono.init.QuadPart) / (double)freq.QuadPart) * 1000.0); \
    }

#elif __linux__
    #include <time.h>
    
    typedef struct
    {
        struct timespec init;
        struct timespec end;
    } cronometer;

#define CRONO_THIS(X /*X is a statement*/)                                                                           \
    {                                                                                                                \
        cronometer crono;                                                                                            \
        clock_gettime(CLOCK_REALTIME, &crono.init);                                                                  \
        X;                                                                                                           \
        clock_gettime(CLOCK_REALTIME, &crono.end);                                                                   \
        printf(#X " in %f millisecs\n",                                                                              \
               (float)(1.0 * (1.0 * ts2.tv_nsec - ts1.tv_nsec * 1.0) * 1e-9 + 1.0 * ts2.tv_sec - 1.0 * ts1.tv_sec)); \
    }

#endif

double performancecounter_diff(cronometer *crono);
void cronoStart(cronometer *crono);
void cronoPause(cronometer *crono);
double cronoStop(cronometer *crono);
void cronoStopP(cronometer *crono);
double cronoCheck(cronometer *crono);
void cronoCheckP(cronometer *crono);