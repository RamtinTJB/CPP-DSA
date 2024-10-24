#include <sys/inotify.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + 16))  // Define a custom buffer size

int main() {
    int fd, wd;
    char buffer[BUF_LEN];
    off_t last_position = 0;

    // Initialize inotify instance
    fd = inotify_init1(IN_NONBLOCK);  // Use non-blocking mode
    
    if (fd < 0) {
        perror("inotify_init1");
        return 1;
    }

    // Watch for changes in the log file
    wd = inotify_add_watch(fd, "/logs/logfile.log", IN_MODIFY);
    
    if (wd < 0) {
        perror("inotify_add_watch");
        return 1;
    }

    // Open the log file for reading
    int logfile = open("/logs/logfile.log", O_RDONLY);
    if (logfile < 0) {
        perror("open");
        return 1;
    }

    // Setup for select()
    fd_set rfds;
    int retval;
    struct timeval tv;

    while (1) {
        // Clear the file descriptor set and add our inotify file descriptor
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        // Set a timeout for select() if needed, or leave NULL to block indefinitely
        tv.tv_sec = 5;   // Timeout after 5 seconds (optional, can be NULL for infinite block)
        tv.tv_usec = 0;

        // Wait for the inotify descriptor to be ready for reading
        retval = select(fd + 1, &rfds, NULL, NULL, &tv);

        if (retval == -1) {
            perror("select()");
            break;
        } else if (retval) {
            // There is data available to read from inotify
            int length = read(fd, buffer, BUF_LEN);
            if (length < 0 && errno != EAGAIN) {
                perror("read");
                break;
            }

            if (length > 0) {
                // An event occurred; let's check what happened
                struct inotify_event *event = (struct inotify_event *) &buffer[0];

                if (event->mask & IN_MODIFY) {
                    // Log file was modified, read and print new lines

                    // Seek to the last read position
                    if (lseek(logfile, last_position, SEEK_SET) < 0) {
                        perror("lseek");
                        break;
                    }

                    // Read new data from the file
                    char read_buffer[1024];
                    ssize_t bytes_read;
                    while ((bytes_read = read(logfile, read_buffer, sizeof(read_buffer) - 1)) > 0) {
                        // Null-terminate and print the new lines
                        read_buffer[bytes_read] = '\0';
                        printf("%s", read_buffer);
                    }

                    // Update the last position to where we finished reading
                    last_position = lseek(logfile, 0, SEEK_CUR);
                }
            }
        } else {
            // Timeout occurred, no event detected
            printf("No changes detected in the last 5 seconds.\n");
        }
    }

    // Cleanup
    close(logfile);
    inotify_rm_watch(fd, wd);
    close(fd);
    
    return 0;
}

