#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

char global_path[256];

void handle_sigterm(int sig) {
    unlink(global_path);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    char target_char = argv[1][0];
    strncpy(global_path, argv[2], 255);

    signal(SIGTERM, handle_sigterm);
    signal(SIGINT, handle_sigterm);

    size_t buf_size = 4096;
    char buffer[buf_size];
    memset(buffer, target_char, buf_size);

    unlink(global_path);

    if (mkfifo(global_path, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    while (1) {
        int fd = open(global_path, O_WRONLY);
        if (fd == -1) {
            sleep(1);
            continue;
        }
        signal(SIGPIPE, SIG_IGN); 
        while (write(fd, buffer, buf_size) > 0) {}
        close(fd);
    }
    return 0;
}
