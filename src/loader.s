; // Multiboot Header (without this, GRUB would not recognize the kernel)
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1) # align, provide mem map
.set CHECKSUM, -(MAGIC + FLAGS)
.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM



.section .text
.extern initialiseConstructors
.extern kernelMain
.global loader

loader:
    mov $kernel_stack, %esp       ; // Stack initialisieren
    push %eax                     ; // Multiboot-Magicnumber auf den Stack legen
    push %ebx                     ; // Adresse der Multiboot-Structure auf den Stack legen
    call initialiseConstructors   ; // Konstruktoren aufrufen
    call kernelMain               ; // kernelMain aufrufen

_stop:
    cli
    hlt
    jmp _stop



.section .bss
.space 2*1024*1024 ; // 2 MiB Stack
kernel_stack:
