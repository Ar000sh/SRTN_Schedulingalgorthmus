cmake_minimum_required(VERSION 3.19)
project(clion C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(clion
        bs_types.h
        core.c
        core.h
        dispatcher.c
        dispatcher.h
        globals.h
        log.c
        log.h
        main.c
        processcontrol.c
        processcontrol.h
        scheduler.c
        scheduler.h
        simruntime.c
        simruntime.h)
