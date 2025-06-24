#!/bin/bash
# first run ending commands like start a service, copy a file etc, at the end put a command starting a program
export ipv4_address=$(echo | hostname -i)
export OS=$(cat /etc/os-release | grep PRETTY_NAME | cut -d "=" -f2)
sed -i 's|%CONTAINER_NAME%|'"$CONTAINER_NAME"'|g' /var/www/html/index.html
sed -i 's|%container_hostname%|'"$HOSTNAME"'|g' /var/www/html/index.html 
sed -i 's|%ipv4_address%|'"$ipv4_address"'|g' /var/www/html/index.html
sed -i 's|%OS%|'"$OS"'|g' /var/www/html/index.html
sed -i 's|%main_owner%|'"$OWNER"'|g' /var/www/html/index.html
service ssh start && sleep 10 && /usr/sbin/apache2ctl -DFOREGROUND