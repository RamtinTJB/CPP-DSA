# Use an official minimal Debian image with gcc
FROM debian:latest

# Install required packages: gcc, make, and necessary libraries
RUN apt-get update && apt-get install -y \
    gcc \
    libc6-dev \
    inotify-tools \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy the C file and the shell script into the container
COPY watcher.c /app/watcher.c
COPY start.sh /app/start.sh

# Make the start script executable
RUN chmod +x /app/start.sh

# Compile the C program
RUN gcc -o watcher watcher.c

# Expose any necessary ports (none in this case, since it's a local file monitor)
# Expose port 8080 (if you have a need for web-based logging later)
EXPOSE 8080

# Run the start script to monitor logs
CMD ["/app/start.sh"]

