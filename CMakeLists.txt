cmake_minimum_required(VERSION 3.16)
project(FHNW_syspr_system_programming)

set(CMAKE_CXX_STANDARD 14)

add_executable(FHNW_syspr_system_programming
        src/andiswiss/w00_introduction/w00a_hello_world.c
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
        src/andiswiss/w01_first_steps_in_c/various_stuff.c
        src/andiswiss/w01_first_steps_in_c/my_range.c
        src/andiswiss/w01_first_steps_in_c/my_args.c
        src/andiswiss/w01_first_steps_in_c/my_tree.c
        src/andiswiss/w02_functions/swap.c
        src/andiswiss/w02_functions/linked_example/linked_main.c
        src/andiswiss/w02_functions/linked_example/linked_f.c
        src/andiswiss/w02_functions/struct.c
        src/andiswiss/w02_functions/my_struct_v2.c
        src/andiswiss/w02_functions/scope.c
        src/andiswiss/w02_functions/heater/heater.c
        src/andiswiss/w02_functions/heater/home.c
        src/andiswiss/w02_functions/garbage.c
        src/andiswiss/w02_functions/map.c
        src/andiswiss/w02_functions/max.c
        src/andiswiss/w02_functions/error.c src/andiswiss/w02_functions/sys_t.c src/andiswiss/w02_functions/my_kilo.c src/andiswiss/w03_file_io/my_copy.c src/andiswiss/w03_file_io/lseek.c src/andiswiss/w03_file_io/my_logger.c src/andiswiss/w03_file_io/stdio_buf.c src/andiswiss/w03_file_io/tmp_file.c src/andiswiss/w03_file_io/my_write_bytes.c src/andiswiss/lib/tlpi_hdr.h src/andiswiss/lib/get_num.h src/andiswiss/lib/error_functions.h)
