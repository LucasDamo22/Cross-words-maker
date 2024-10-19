TARGET = cross.bin

SRCDIR = srcs
INCLUDEDIR = $(SRCDIR)/include

SOURCE = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDEDIR)/*.h)

CC = g++
CFLAGS =  -Wall -Wno-sign-compare -Wno-comment
CFLAGS_DEBUG =  -g

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) -I$(INCLUDEDIR)

debug: $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o $(TARGET) $(SOURCE) -I$(INCLUDEDIR)

clean:
	rm *.bin
    