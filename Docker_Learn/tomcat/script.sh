#!/bin/bash
# first run ending commands like start a service, copy a file etc, at the end put a command starting a program
service ssh start && sleep 10 && /usr/sbin/apache2ctl -DFOREGROUND