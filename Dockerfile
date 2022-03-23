FROM ubuntu:21.10
ARG DEBIAN_FRONTEND=noninteractive
# install make, C++, CMake and python3 pip (for installing conan)
RUN apt-get -qq update && \
    apt-get -qq install -y build-essential cmake python3-pip git
# install and configure conan
RUN pip3 install conan && \
    conan user && \
    conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11 default

COPY ./ /use_metall

RUN mkdir /use_metall/build
WORKDIR /use_metall/build
RUN conan install .. --build=missing
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make -j
RUN ./write_data
RUN ./read_data
