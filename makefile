DOCKER_CMD := $(if $(shell command -v podman), podman, docker)

.PHONY: all build run clean

all: run

build:
	$(DOCKER_CMD) build -t cpp-editor .

run: build
	$(DOCKER_CMD) run -it --rm cpp-editor

clean:
	$(DOCKER_CMD) rmi cpp-editor
