FROM fuzzers/afl:2.52

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake zlib1g zlib1g-dev
RUN git clone https://github.com/jmcnamara/libxlsxwriter.git 
WORKDIR /libxlsxwriter
RUN cmake -DCMAKE_C_COMPILER=afl-clang -DCMAKE_CXX_COMPILER=afl-clang++ -DBUILD_SHARED_LIBS=1 .
RUN make
RUN make install
COPY src/fuzz_png_xlsx.c .
RUN afl-clang -L/usr/local/lib -I/usr/local/include/xlsxwriter/ fuzz_png_xlsx.c -o /fuzz_image_xlsx -lxlsxwriter 
RUN mkdir /xlsxImage-corpus
RUN wget https://file-examples.com/wp-content/uploads/2017/10/file_example_PNG_500kB.png
RUN wget https://file-examples.com/wp-content/uploads/2017/10/file_example_PNG_1MB.png
RUN wget https://people.sc.fsu.edu/~jburkardt/data/png/ajou_logo.png
RUN wget https://people.sc.fsu.edu/~jburkardt/data/png/all_gray.png
RUN wget https://people.sc.fsu.edu/~jburkardt/data/png/brain.png
RUN wget https://people.sc.fsu.edu/~jburkardt/data/png/coins.png
RUN wget https://people.sc.fsu.edu/~jburkardt/data/png/dla.png
RUN mv *.png /xlsxImage-corpus
#RUN export LD_LIBRARY_PATH=.
ENV LD_LIBRARY_PATH=/libxlsxwriter

ENTRYPOINT ["afl-fuzz", "-i", "/xlsxImage-corpus", "-o", "/out-xlsx"]
CMD ["/fuzz_image_xlsx", "@@"]
