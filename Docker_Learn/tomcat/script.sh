#!/bin/bash
# first run ending commands like start a service, copy a file etc, at the end put a command starting a program
sed -i 's|%CONTAINER_NAME%|'"$CONTAINER_NAME"'|g' /var/www/html/index.html
sed -i 's|%container_hostname%|'"$HOSTNAME"'|g' /var/www/html/index.html 
sed -i 's|%ipv4_address%|'"$ipv4_address"'|g' /var/www/html/index.html

service ssh start && sleep 10 && /usr/sbin/apache2ctl -DFOREGROUND