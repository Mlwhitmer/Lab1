EXES = hello

MYCFLAGS= -Wall -I/usr/include
MYLDFLAGS= -L/usr/lib64 -lGL -lglut -lGLU -lm

all: $(EXES)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} $< -o $@

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) ${MYCFLAGS} ${MYLDFLAGS} $^ -o $@

clean:
	rm -f ${EXES} *.o 

hello: hello.c offreader.c jmesh.c utils.c
