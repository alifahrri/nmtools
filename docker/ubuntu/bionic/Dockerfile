FROM ubuntu:bionic

RUN apt update && apt install -y cmake gcc build-essential

WORKDIR /app/numeric_tools/

COPY . /app/numeric_tools/

RUN mkdir build && cd build \
    && cmake .. && make

CMD ["bash","scripts/run_unit_tests.sh"]