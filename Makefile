CXX = g++
CXXFLAGS = -O2 -std=c++11 -I.. -Wall -Wextra -pthread

PREFIX = /usr/local
#PREFIX = $(shell brew --prefix)

OPENSSL_DIR = $(PREFIX)/opt/openssl@1.1
#OPENSSL_DIR = $(PREFIX)/opt/openssl@3
OPENSSL_SUPPORT = -DCPPHTTPLIB_OPENSSL_SUPPORT -I$(OPENSSL_DIR)/include -L$(OPENSSL_DIR)/lib -lssl -lcrypto

ZLIB_SUPPORT = -DCPPHTTPLIB_ZLIB_SUPPORT -lz

BROTLI_DIR = $(PREFIX)/opt/brotli
BROTLI_SUPPORT = -DCPPHTTPLIB_BROTLI_SUPPORT -I$(BROTLI_DIR)/include -L$(BROTLI_DIR)/lib -lbrotlicommon -lbrotlienc -lbrotlidec

all: shakeAPI shakeconsole PutHTML

PutHTML:
	cp shake.html /var/www/html/shakeCpp/
	cp shake.css /var/www/html/shakeCpp/
	cp shake.js /var/www/html/shakeCpp/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/shakeCpp/

textindex.o :	textindex.cpp textindex.h
	$(CXX) $(CXXFLAGS) -c textindex.cpp

shakeAPI : shakeAPI.cpp httplib.h textindex.o
	$(CXX) -o shakeAPI $(CXXFLAGS) shakeAPI.cpp $(OPENSSL_SUPPORT) $(ZLIB_SUPPORT) $(BROTLI_SUPPORT) textindex.o

shakeconsole : textindex.o  shakeconsole.cpp
	$(CXX) -o shakeconsole shakeconsole.cpp textindex.o

pem:
	openssl genrsa 2048 > key.pem
	openssl req -new -key key.pem | openssl x509 -days 3650 -req -signkey key.pem > cert.pem

clean:
	rm shakeconsole shakeAPI *.o  *.pem
