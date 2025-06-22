#!/bin/bash
docker run --name my_python --mount type=bind,source="${PWD}"/codes,destination=/root/codes -d -it python:3.11.1
