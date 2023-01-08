LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
CFLAGS = -Wall -I../../sdk/include/ -I../include/

# Should be equivalent to your list of C files, if you don't build selectively
CFILES = $(wildcard *.c)
ifeq ($(CLANG),)
CLANG=clang-15
endif
#FLAGS = -r -flto -O3 -nostdlib -fno-builtin -ffreestanding -mexec-model=reactor --target=wasm32 -Wl,--strip-all -Wl,--initial-memory=131072 -Wl,--max-memory=131072 -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic
FLAGS = -r -nostdlib -fno-builtin -ffreestanding -mexec-model=reactor --target=wasm32 -Wl,--strip-all -Wl,--initial-memory=131072 -Wl,--max-memory=131072 -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic

WASMS = $(patsubst %.c, %.wasm, $(CFILES))
WATS = $(patsubst %.c, %.wat, $(CFILES))

%.wasm: %.c
	$(CLANG) -o $@ $^ $(FLAGS) $(CFLAGS)

%.wat: %.wasm
	wasm2wat $^ -o $@

all: $(WASMS) $(WATS)

clean:
	rm -f *.wasm *.wat
