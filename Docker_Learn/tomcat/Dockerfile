# ----------------------------------
# Dockerfile building a Docker image
# with a APACHE and wbcontent in it--
# ----------------------------------
# ----By Rishat Mukhtarov-----------
FROM ubuntu:16.04

LABEL author=Rishat_Mukhtarov

RUN apt-get -y update
RUN apt-get -y install apache2
# RUN systemctl enable apache2
RUN apt-get -y install nmap
RUN apt-get -y install mc
RUN apt-get -y install vim


RUN apt-get -y install openssh-server
RUN sed -i '/\(^PermitRootLogin\).*/ s//\PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/^#\(.*PasswordAuthentication yes.*\)/\1/' /etc/ssh/sshd_config
# RUN sed -i -e 's/# PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config
# RUN echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config
# RUN echo -e "1234qwerty\n1234qwerty" | passwd root
RUN echo 'root:1234qwerty' | chpasswd


# RUN echo 'Hey all, APACHE running, ubuntu container running, gonna be all right' > /var/www/html/index.html
# RUN cat /var/www/html/index.html

COPY ./index.html /var/www/html
COPY ./*.JPG /var/www/html
COPY ./script.sh /app/script.sh
RUN chmod +x /app/script.sh

# COPY ./index.html /usr/share/nginx/html
# COPY ./*.JPG /usr/share/nginx/html

CMD ["/app/script.sh"]
#CMD ["/usr/sbin/apache2ctl", "-DFOREGROUND"; "/etc/systemd/system/sshd.service", "start"]


EXPOSE 80
EXPOSE 22

