gcc -std=c99 -DPIC10F200 -lm -lrt -pthread -Wall -g -o simulator-gui Fetch.c clock.c -export-dynamic `pkg-config --cflags --libs gtk+-3.0`
