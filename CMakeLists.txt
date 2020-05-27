cmake_minimum_required(VERSION 3.16)
project(FHNW_syspr_system_programming)

set(CMAKE_CXX_STANDARD 14)

add_executable(FHNW_syspr_system_programming
        src/andiswiss/w00a_hello_world.c
        src/andiswiss/makefile
        src/libs/my_stdlib.c
        src/mikenoethiger/libs/my_stdlib.c
        src/mikenoethiger/echo-client.c
        src/mikenoethiger/echo-server.c
        src/mikenoethiger/fifo1.c
        src/mikenoethiger/fifo2.c
        src/mikenoethiger/http-client.c
        src/mikenoethiger/http-server.c
        src/mikenoethiger/makefile
        src/mikenoethiger/mqattr.c
        src/mikenoethiger/mqcreate.c
        src/mikenoethiger/mqrec.c
        src/mikenoethiger/mqsend.c
        src/mikenoethiger/mutex1.c
        src/mikenoethiger/mutex2.c
        src/mikenoethiger/pipe1.c
        src/mikenoethiger/pipe2.c
        src/mikenoethiger/pipe3.c
        src/mikenoethiger/pipe4.c
        src/mikenoethiger/semaphore1.c
        src/mikenoethiger/semaphore2.c
        src/mikenoethiger/semaphore3.c
        src/mikenoethiger/stream-client.c
        src/mikenoethiger/stream-server.c
        src/mikenoethiger/terminal1.c
        src/mikenoethiger/thread1.c
        src/mikenoethiger/thread2.c
        src/mikenoethiger/time1.c
        src/mikenoethiger/time2.c
        src/mikenoethiger/time3.c
        src/mikenoethiger/time4.c
        src/makefile
        src/andiswiss/w01a_various_stuff.c
        src/andiswiss/w01_hands_on/my_range.c src/andiswiss/w01_hands_on/my_args.c src/andiswiss/w01_hands_on/my_tree.c)
