cmake_minimum_required(VERSION 3.25)
project(philo C)

set(CMAKE_C_STANDARD 11)

include_directories(philo/include)

add_executable(philo
        philo/include/fork.h
        philo/include/philo.h
        philo/include/print.h
        philo/src/fork.c
        philo/src/main.c
        philo/src/parser.c
        philo/src/philo.c
        philo/src/philo_eat.c
        philo/src/philo_equalizer.c
        philo/src/philo_init.c
        philo/src/philo_print.c
        philo/src/philo_utils.c philo/src/philo_clear.c)
