#!/bin/bash

# Build if not yet build
make all

# Execute kernel in VM
qemu-system-i386 -cdrom bin/kernel.iso
