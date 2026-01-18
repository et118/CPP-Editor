@echo off

docker build -t cpp-editor .
docker run -it --rm cpp-editor