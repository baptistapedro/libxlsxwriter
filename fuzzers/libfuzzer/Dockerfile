FROM fuzzers/libfuzzer:12.0

RUN apt install -y build-essential wget git clang cmake zlib1g zlib1g-dev
RUN git clone https://github.com/jmcnamara/libxlsxwriter.git 
WORKDIR /libxlsxwriter
RUN cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=1 .
RUN make
RUN make install
COPY src/fuzz_write_string.c /libxlsxwriter/fuzz_write_string.c
RUN clang-12 -L/usr/local/lib -I/usr/local/include/xlsxwriter/ -fsanitize=fuzzer,address fuzz_write_string.c -o /fuzz_ws -lxlsxwriter
ENV LD_LIBRARY_PATH=/usr/local/lib

# Set to fuzz!
ENTRYPOINT []
CMD /fuzz_ws
