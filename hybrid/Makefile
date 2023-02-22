LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
SDK_DIR = ../sdk
CFLAGS = -Wall -I$(SDK_DIR)/c/sdk/include/ -I$(SDK_DIR)/c/hash/include/ -I$(SDK_DIR)/c/rlp/include/

# Should be equivalent to your list of C files, if you don't build selectively
CFILES = $(wildcard *.c)
ifeq ($(CLANG),)
CLANG=clang-15
endif
FLAGS = -flto -O3 -nostdlib -fno-builtin -ffreestanding -mexec-model=reactor --target=wasm32 -Wl,--strip-all -Wl,--initial-memory=131072 -Wl,--max-memory=131072 -Wl,--no-entry -Wl,--allow-undefined -Wl,--export-dynamic

all: output.wasm

inner.wasm: inner.ts
	asc inner.ts -O --runtime stub --noAssert --lib -o inner_pre.wasm
	wasm2wat inner_pre.wasm -o inner.wat
	wat2wasm inner.wat -r -o inner.wasm

sdk-final.wasm: inner.wasm
	sh $(SDK_DIR)/scripts/build.sh sdk.wasm
	wasm-ld-15 -r sdk.wasm inner.wasm -o sdk-final.wasm

output.wasm:# $(CFILES ) sdk-final.wasm inner.wasm
	$(CLANG) -o $@ $(CFILES) sdk-final.wasm $(FLAGS) $(CFLAGS)


clean:
	sh $(SDK_DIR)/scripts/clean.sh
	rm -f *.wasm *.wat
