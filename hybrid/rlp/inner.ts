export function crash(
  message: string | null,
  fileName: string | null,
  lineNumber: u32,
  columnNumber: u32,
): void {
  unreachable();
}

declare function get_byte(x: u32): u32;
export function select(): i32{
    return get_byte(0);
}
