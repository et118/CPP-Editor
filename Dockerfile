FROM docker.io/library/alpine:3.23.2

RUN apk update && apk add --no-cache cmake build-base python3

WORKDIR /app

COPY . /app

RUN cmake -S . -B build

RUN cmake --build build

CMD ["./build/CPP-Editor", "/app/TestArea"]
