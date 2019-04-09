cmake_minimum_required(VERSION 3.12)
project(embedded C)

set(CMAKE_C_STANDARD 99)

add_executable(embedded main.c time_record.c producer.c customer.c lock_set.c multi_proc.c)