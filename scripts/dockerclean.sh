#!/bin/bash

#delete containers
docker rm $(docker ps -a -q)

#delete images
docker rmi $(docker images -q)
