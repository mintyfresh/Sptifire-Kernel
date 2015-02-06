#!/bin/bash

# Build if not yet build
make all || exit 1

# Execute kernel in VM
qemu-system-i386 -cdrom bin/kernel.iso
