extern crate libc;
use wasm_bindgen::prelude::*;

const SHA256_DIGEST_LENGTH: usize = 256;

extern {
    fn Hash_Init(param: u32);
    fn Hash_Update(
        //data: *const u8,
        length: usize,
    );
    fn Hash_Final(out: *mut u8);
}

pub fn zkwasm_sha256_init() {
    unsafe { Hash_Init(256) };
}

pub fn zkwasm_sha256_update(data: &[u8]) {
    {
        unsafe {
            Hash_Update(
                //data.as_ptr(),
                data.len(),
            )
        };
    }
}

pub fn zkwasm_sha256_finalize() -> Vec<u8> {
    let mut output = [0; SHA256_DIGEST_LENGTH / 8];
    unsafe { Hash_Final(output.as_mut_ptr()) }
    output.to_vec()
}

#[wasm_bindgen]
pub fn zkwasm_sha256_digest(data: &[u8]) -> Vec<u8> {
    zkwasm_sha256_init();
    zkwasm_sha256_update(data);
    zkwasm_sha256_finalize()
}

#[cfg(test)]
mod tests {
    use crate::*;

    #[test]
    fn test_empty_msg() {
        println!("{:?}", zkwasm_sha256_digest(&[]));
    }
}
