//
//CC = gcc -Wall -std=c11 -ggdb
//
//
//all: static shared clean
//
//static:
//    $(CC) $(CFLAGS) -c first_library.c -o first_library.o
//    ar rcs libfirst_library.a first_library.o
//
//shared:
//    $(CC) $(CFLAGS) -fPIC -c first_library.c -o first_library.o
//    $(CC) $(CFLAGS) -shared -o libfirst_library.so first_library.o
//
//clean:
//    rm -rf *.o *.a *.so main temp