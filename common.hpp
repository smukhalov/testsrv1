#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <unordered_map>
#include <mutex>

#include "http_parser.h"

#define WORKERS_NUM 4
#define EPOLL_MAXEVENTS 64

struct worker_ctx;
struct server_ctx;
static http_parser_settings parser_settings;

#define SETSTRING(s,val) s.value=val; s.length=STRLENOF(val)
#define APPENDSTRING(s,val) memcpy((char*)s->value + s->length, val, STRLENOF(val)); s->length+=STRLENOF(val)

static std::mutex mtx;

static inline int log(char *buf, size_t nread) {

    return 0;
    /*std::lock_guard<std::mutex> lck (mtx);

    FILE* out;
    if ((out = fopen("/tmp/final.log", "a+")) == NULL) {
        perror("!!! Fail to open file");
        return 1;
    }

    size_t written = fwrite(buf, 1, nread, out);
    fprintf(stdout, "written to log: %d bytes\n", written);
    fclose(out);*/
}

/**
 * Set socket to Non-blocking mode
 */
static inline int make_socket_non_blocking(int sfd) {
    int flags, s;

    flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if (s == -1) {
        perror("fcntl");
        return -1;
    }

    return 0;
}

inline bool file_exists (const std::string& name) {
    struct stat buffer;
    if (stat (name.c_str(), &buffer) != 0) {
        return false;
    }

    struct stat path_stat;
    stat(name.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);

}