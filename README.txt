https://github.com/ritchie229/WorkSpace/tree/main/Docker_Learn

======================================================

docker pull ritchie229/ritchie_docker:net_containers
docker pull ghcr.io/ritchie229/net_containers:latest

=========
DOCKERFILE
=========
FROM ubuntu:16.04
LABEL author=Rishat_Mukhtarov
ENV OWNER=Rishat_Mukhtarov
RUN apt-get -y update
RUN apt-get -y install apache2
RUN apt-get -y install nmap
RUN apt-get -y install mc
RUN apt-get -y install vim
RUN apt-get -y install openssh-server
RUN sed -i '/\(^PermitRootLogin\).*/ s//\PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/^#\(.*PasswordAuthentication yes.*\)/\1/' /etc/ssh/sshd_config
RUN echo 'root:1234qwerty' | chpasswd
COPY ./index.html /var/www/html
COPY ./*.JPG /var/www/html
COPY ./script.sh /app/script.sh
RUN chmod +x /app/script.sh
CMD ["/app/script.sh"]
EXPOSE 80
EXPOSE 22

=========
script.sh
=========
#!/bin/bash
first run ending commands like start a service, copy a file etc, at the end put a command starting a program
export ipv4_address=$(echo | hostname -i)
export OS=$(cat /etc/os-release | grep PRETTY_NAME | cut -d "=" -f2)
sed -i 's|%CONTAINER_NAME%|'"$CONTAINER_NAME"'|g' /var/www/html/index.html
sed -i 's|%container_hostname%|'"$HOSTNAME"'|g' /var/www/html/index.html 
sed -i 's|%ipv4_address%|'"$ipv4_address"'|g' /var/www/html/index.html
sed -i 's|%OS%|'"$OS"'|g' /var/www/html/index.html
sed -i 's|%main_owner%|'"$OWNER"'|g' /var/www/html/index.html
service ssh start && sleep 10 && /usr/sbin/apache2ctl -DFOREGROUND

=========
CLI
=========
docker run -d --rm --name net_container_05 -e CONTAINER_NAME=net_container_05 -e OWNER=Leysanchik! -p 85:80 ritchie229/ritchie_docker:net_containers

=========
Docker Compose YML
=========
version: '3.5'

services:
  net_container_10:
    image: ritchie229/ritchie_docker:net_containers
    #build: .
    container_name: net_container_10
    ports:
      - "8010:80"
      - "2210:22"
    restart: unless-stopped
    environment:
      - 'OWNER=Ritchie'
    depends_on:
      - net_container_11
    networks:
      - HomeBridge
    


  net_container_11:
    image: ritchie229/ritchie_docker:net_containers
    #build: .
    container_name: net_container_11
    ports:
      - "8011:80"
      - "2211:22"
    restart: unless-stopped
    environment:
      - 'OWNER=Leysanchik'
    networks:
      - HomeBridge
  
networks:
  HomeBridge:
    external: true
    name: HomeBridge
==========================================================
                        THE END
==========================================================
