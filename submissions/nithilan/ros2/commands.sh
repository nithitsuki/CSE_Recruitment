#!/bin/sh
podman build -t my_ros_image .
podman run -it --rm \
  --net=host \
  --privileged \
  -v /dev:/dev \
  my_ros_image

