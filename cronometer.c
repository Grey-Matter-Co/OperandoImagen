#include "cronometer.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>

    double performancecounter_diff(cronometer *crono)
    {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        return (double)(crono->end.QuadPart - crono->init.QuadPart) / (double)freq.QuadPart;
    }

    void cronoStart(cronometer *crono)
    {
        QueryPerformanceCounter(&crono->init);
    }

    void cronoPause(cronometer *crono)
    {
        QueryPerformanceCounter(&crono->end);
    }

    double cronoStop(cronometer *crono)
    {
        double secs;
        QueryPerformanceCounter(&crono->end);
        secs = performancecounter_diff(crono) *1000.0;

        printf("%.16g millisecs\n", secs);
        return secs;
    }
    void cronoStopP(cronometer *crono)
    {
        QueryPerformanceCounter(&crono->end);
        printf("%.16g millisecs\n", 
                performancecounter_diff(crono) * 1000.0);
    }

    double cronoCheck(cronometer *crono)
    {
        double secs;
        secs = performancecounter_diff(crono) * 1000.0;

        printf("%.16g millisecs\n", secs);
        return secs;
    }
    void cronoCheckP(cronometer *crono)
    {
        printf("%.16g millisecs\n",
               performancecounter_diff(crono) * 1000.0);
    }
#elif __linux__
    #include <time.h>

    double performancecounter_diff(cronometer *crono)
    {
        return (double) 1.0 * (1.0 * crono->end.tv_nsec - crono->init.tv_nsec * 1.0) * 1e-9 + 1.0 * crono->end.tv_sec - 1.0 * crono->init.tv_sec;
    }

    void cronoStart(cronometer *crono)
    {
        clock_gettime(CLOCK_REALTIME, &crono->init);
    }

    void cronoPause(cronometer *crono)
    {
        clock_gettime(CLOCK_REALTIME, &crono->end);
    }

    double cronoStop(cronometer *crono)
    {
        double secs;
        clock_gettime(CLOCK_REALTIME, &crono->end);
        secs = performancecounter_diff(crono);

        printf("%f secs\n", secs);
        return secs;
    }
    void cronoStopP(cronometer *crono)
    {
        QueryPerformanceCounter(&crono->end);
        printf("%f secs\n",
            performancecounter_diff(crono));
    }

    double cronoCheck(cronometer *crono)
    {
        double secs;
        secs = performancecounter_diff(crono);

        printf("%f secs\n", secs);
        return secs;
    }
    void cronoCheckP(cronometer *crono)
    {
        printf("%f secs\n",
            performancecounter_diff(crono));
    }
#endif