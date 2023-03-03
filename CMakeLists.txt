cmake_minimum_required(VERSION 3.24)
project(philo C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(philo
        include/fork.h
        include/philo.h
        src/fork.c
        src/main.c
        src/parser.c
        src/philo.c
        src/philo_init.c src/philo_print.c)
