    .intel_syntax noprefix
    .global load_gdt
    .global store_gdt

load_gdt:
    lgdt [rdi]          # Load the gdt into its new place.
    xor rax, rax
    mov ax, 0x10        # Load all the data segments with the proper gdt selector
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    pop rax
    pushq 0x08          # Put the code selector on the stack
    pushq rax           # Put the return address back
    retfq               # Get out of here and return back with the new gdt and segment registers!!!

store_gdt:
    sgdt [rdi]
    ret
