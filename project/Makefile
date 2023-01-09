LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
CFLAGS = -Wall -I../sdk/c/sdk/include/ -I../sdk/c/hash/include/

# Should be equivalent to your list of C files, if you don't build selectively
CFILES = $(wildcard *.c)
ifeq ($(CLANG),)
CLANG=clang-15
endif
FLAGS = -flto -O3 -nostdlib -fno-builtin -ffreestanding -mexec-model=reactor --target=wasm32 -Wl,--strip-all -Wl,--initial-memory=131072 -Wl,--max-memory=131072 -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic

all: output.wasm

sdk.wasm:
	sh ../sdk/scripts/build.sh sdk.wasm

output.wasm: $(CFILES ) sdk.wasm
	$(CLANG) -o $@ $(CFILES) sdk.wasm $(FLAGS) $(CFLAGS)


clean:
	sh ../sdk/scripts/clean.sh
	rm -f *.wasm *.wat
