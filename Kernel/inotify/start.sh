#!/bin/bash

# Ensure the log file exists
if [ ! -f /logs/logfile.log ]; then
    touch /logs/logfile.log
fi

# Start the watcher program
/app/watcher

