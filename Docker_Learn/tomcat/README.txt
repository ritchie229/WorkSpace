To pull an image from dockerhub # docker pull <image_name> (eg. # docker pull nginx).
To search for a specific image in dockerhub # docker search <image_name> (eg. # docker search tomcat).
You can eather pull an image from the hub and run it or you can run it diretly, it will automatically pull it, then create a container.

# docker images - show the images you have locally.
# docker rmi - to delete a specific image. Note, If there is a container created upun the base of the image, you should firt stop the container and remove it. 


# docker build -t <new_image_name:tag> . - builds a new image on the basis of a sample image from dockerhub and the custom requirements described in the Dockerfile (should be in the same dir where PWD).

eg.with build from CLI
# docker build -t my-ubuntu -<<EOF
FROM ubuntu:22.04
RUN apt update && apt install iputils-ping --yes
EOF

# docker run <options> <image_name:tag> - creates a container. Keys:
    -it (interactive)/-d (daemon), 
    -p 1234:8080 (forwards 8080 to 0.0.0.0 port 1234/tcp), 
    --rm (removes created container when stopped), 
    -- name <custom_container_name>
    -e (extra variables)
    -v (volumes you map, eg.: 
        docker run -p 80:80 -v /opt/nginx/data:/usr/share/nginx/html -d nginx (your constant data in directory you created)
        docker run -p 80:80 -v /usr/share/nginx/html -d nginx (it itself creates a place for data on the server at /var/lib/docker/<HASH>)
        docker run -p 80:80 -v <volume_name>:/usr/share/nginx/html -d nginx (it itself creates a place for data on the server at /var/lib/docker/<volume_name>
        Note, the path for the MacOS is the same, but it is not on the host FS, but inside the Docker VM. The best way to access the volumes here is to use VSCode Docker extention installed. Click on Docker icon, go to VOLUMES section, find your volume you want to modify, right-click on it and choose Explore in a Dev Container. In the new VSCode window you will see the contents ov the volume, and you can just use Drag-n-Drop or edit options.
        Also you can run the following to enter into Docker VM and modify: "# docker run -it --privileged --pid=host debian nsenter -t 1 -m -u -n -i sh"
    --mount
# docker volume ls - lists volumes
# docker volume create <volume_name>
# docker volume rm <volume_name>
--------------
eg.with mounting volume
# docker volume create <volume_name>
# docker run --mount source=<volume_name>,destination=</destination_path/> ubuntu:22.04
# dcoker run -it --rm --mount type=bind,source="${PWD}"/my-data,destination=/my-data ubuntu:22.04
--------------
eg.
docker run --name my_python --mount type=bind,source="${PWD}"/codes,destination=/root/codes -d -it python:3.11.1
docker run --name my_python -v "${PWD}":/root/codes -d -it python:3.11.1
docker commit ea13cdab186f ritchie229/ritchie_docker:my_python
docker run --name my_python -d -it ritchie229/ritchie_docker:my_python
docker exec -it my_python /bin/bash
The mounting will not happen!!!
--------------
eg.
docker build -t ritchie229/ritchie_docker:my-python -<<EOF
FROM python:3.11.1
WORKDIR /root/codes
COPY . .
EOF
docker run --name my_python -d -it ritchie229/ritchie_docker:my-python
docker exec -it my_python /bin/bash
docker stop my_python && docker rm my_python
-------------

    sleep 900 (delays stop time to 15 minutes).

# docker ps - shows the running containers (option -a shows all existing containers).
# docker stop/start/pause/unpause <container/id> - stops/starts/pauses/unpauses the existing container.
# docker rm <container/id> - removes the container.

# docker exec -it <container_id> /bin/bash - lets you enter inside the container and make changes.

# docker inspect <container_id> - shows settings inside container
# docker stats <container_id> - shows hardware usage statistics
# docker logs <container_id> - shows syslogs of the container. Keys:
    - f (realtime)

# docker commit <container_id> <new_image_name:tag> - lets you create a new image on the basis of an existing container.

To push to your dockerhub repository:
# docker login
# docker tag <your_image_name> <your_dockerhub_username>/<your_repository_name>:<version> (eg. docker tag rishat:v2 ritchie229/ritchie_docker:tomcat_app)
# docker push <your_dockerhub_username>/<your_repository_name>:<version> (eg. docker push ritchie229/ritchie_docker:tomcat_app)


Here is a section devoted to Docker Networking

# docker network ls - lists the docker networks
# docker network create <NAME> - creates a network with a bridge drive
# docker network create --drive (-d) host/bridge/none/ipvlan/macvlan/ <NAME> - creates a network with a host/bridge/none/ipvlan/macvlan drive
# docker network inspect <NETWORK_id/NAME> - will show subnet and gw of the network, containers attached and the options applied like type, nat, name, mtu etc.
# docker network create -d bridge --subnet 192.168.10.0/24 --gateway 192.168.10.1 MyNet192 - example
# docket netwok rm <NETWORK_id/NAME> - to remove a network
# docket netwok connect <NETWORK_id/NAME> <container_id> - adding the container to another network
# docket netwok disconnect <NETWORK_id/NAME> <container_id> - disconnects container from any network
-----------
examples:
# docker network create -d macvlanc--subnet 192.168.0.0/24 --gateway 192.168.0.2 --ip-range 192.168.0.200/30 MACVLAN_0
# docker network  connect MACVLAN_0 net_container_01
# docker run -d --name net_container_03 --ip 192.168.0.202 --net MACVLAN_0 -p 83:80 net_containers
------------
# docker run -d --rm --name net_container_05 -e CONTAINER_NAME=net_container_05 -e OWNER=Leysanchik! -p 85:80 ritchie229/ritchie_docker:net_containers
DockerFile



Docker Compose
