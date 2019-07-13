FROM centos:7

RUN yum update && yum install -y cmake gcc build-essential git

WORKDIR /opt/

RUN git clone -b 'release-1.8.1' https://github.com/google/googletest.git

RUN cd googletest \
    && mkdir build && cd build \
    && cmake .. && make && make install

WORKDIR /app/numeric_tools/

COPY . /app/numeric_tools/

RUN mkdir build && cd build \
    && cmake .. && make

CMD ["bash","scripts/run_unit_tests.sh"]