To pull an image from dockerhub # docker pull <image_name> (eg. # docker pull nginx).
To search for a specific image in dockerhub # docker search <image_name> (eg. # docker search tomcat).
You can eather pull an image from the hub and run it or you can run it diretly, it will automatically pull it, then creat a container.

# docker images - show the images you have locally.
# docker rmi - to delete a specific image.


# docker build -t <new_image_name:tag> - builds a new image on the basis of a sample image from dockerhub and the custom requirements described in the Dockerfile (should be in the same dir where PWD).

# docker run <options> <image_name:tag> - creates a container. -it (interactive)/-d (daemon), -p 1234:8080 (forwards 8080 to 0.0.0.0 port 1234/tcp).
# docker ps - shows the running containers (option -a shows all existing containers).
# docker stop/start <container/id> - stops/starts the existing container.
# docker rm <container/id> - removes the container.

# docker exec -it <container_id> /bin/bash - lets you enter inside the container and make changes.

# docker commit <container_id> <new_image_name:tag> - lets you create a new image on the basis of an existing container.

To push to your dockerhub repository:
# docker login
# docker tag <your_image_name> <your_dockerhub_username>/<your_repository_name>:<version> (eg. docker tag rishat:v2 ritchie229/ritchie_docker:tomcat_app)
# docker push <your_dockerhub_username>/<your_repository_name>:<version> (eg. docker push ritchie229/ritchie_docker:tomcat_app)
