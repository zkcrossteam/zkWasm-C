LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
SDK_DIR = ../../sdk
CFLAGS = -Wall -I$(SDK_DIR)/c/sdk/include/ -I$(SDK_DIR)/c/hash/include/ -I$(SDK_DIR)/c/rlp/include/

# Should be equivalent to your list of C files, if you don't build selectively
CFILES = $(wildcard *.c)
ifeq ($(CLANG),)
CLANG=clang-15
endif
FLAGS = -flto -O3 -nostdlib -fno-builtin -ffreestanding -mexec-model=reactor --target=wasm32 -Wl,--initial-memory=131072 -Wl,--strip-all -Wl,--max-memory=131072 -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic -Wl,--features=mutable-globals

all: output.wasm

inner.wasm: inner.ts
	asc inner.ts -o inner_pre_pre.wasm --runtime stub --use abort=inner/crash --disable bulk-memory --disable mutable-globals
	wasm-opt -Oz inner_pre_pre.wasm -o inner_pre.wasm --disable-bulk-memory --disable-mutable-globals
	wasm2wat inner_pre.wasm -o inner_pre.wat --inline-exports --generate-names --disable-bulk-memory --disable-mutable-globals
	wat2wasm inner_pre.wat -r -o inner.wasm

sdk.wasm: inner.wasm
	sh $(SDK_DIR)/scripts/build.sh sdk.wasm

output.wasm: $(CFILES) sdk.wasm inner.wasm
	$(CLANG) -o $@ main.c sdk.wasm inner.wasm $(FLAGS) $(CFLAGS)

clean:
	sh $(SDK_DIR)/scripts/clean.sh
	rm -f *.wasm *.wat
