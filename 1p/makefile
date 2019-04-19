XX = g++
CC = gcc
CFLAGS = -Wall -O -g
TARGET = test

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

#下面的版本时编译链接该文件夹下所有的文件，编译指定文件用上面两行
SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
$(TARGET): $(OBJS)
	$(XX) $(OBJS) -o $(TARGET) 

clean:
	rm -rf *.o test
