FROM ubuntu:latest
RUN apt update -y && apt upgrade -y
RUN apt install g++ valgrind make time -y
COPY . .
CMD make local
