# ----------------------------------
# Dockerfile building a Docker image
# with a APACHE and wbcontent in it--
# ----------------------------------
# ----By Rishat Mukhtarov-----------
FROM ubuntu:16.04

RUN apt-get -y update
RUN apt-get -y install apache2

#RUN echo 'Hey all, APACHE running, ubuntu container running, gonna be all right' > /var/www/html/index.html
#RUN cat /var/www/html/index.html

COPY ./index.html /var/www/html
COPY ./*.JPG /var/www/html
#COPY ./index.html /usr/share/nginx/html
#COPY ./*.JPG /usr/share/nginx/html

CMD ["/usr/sbin/apache2ctl", "-DFOREGROUND"]

EXPOSE 80
