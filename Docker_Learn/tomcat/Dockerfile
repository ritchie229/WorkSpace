# ----------------------------------
# Dockerfile building a Docker image
# with a APACHE and wbcontent in it--
# ----------------------------------
# ----By Rishat Mukhtarov-----------
FROM ubuntu:latest

LABEL author=Rishat_Mukhtarov

RUN apt-get -y update
RUN apt-get -y install apache2
RUN systemctl enable apache2
RUN apt-get -y install nmap
RUN apt-get -y install mc


# RUN echo 'Hey all, APACHE running, ubuntu container running, gonna be all right' > /var/www/html/index.html
# RUN cat /var/www/html/index.html

COPY ./index.html /var/www/html
COPY ./*.JPG /var/www/html
# COPY ./index.html /usr/share/nginx/html
# COPY ./*.JPG /usr/share/nginx/html

# CMD ["/usr/sbin/apache2ctl", "-DFOREGROUND"]

EXPOSE 80
EXPOSE 22
