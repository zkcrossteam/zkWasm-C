export function crash(
  message: string | null,
  fileName: string | null,
  lineNumber: u32,
  columnNumber: u32,
): void {
  unreachable();
}

declare function get_byte(x: u32): u32;
export function compare(): i32{
    let e = new Uint32Array(32);
    return get_byte(0) - get_byte(1);
}
