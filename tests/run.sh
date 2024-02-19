#!/bin/bash
#
#

echo -n -e "$1" > input.txt
openssl enc -e -aes-256-ecb \
  -K 3131313131313131313131313131313131313131313131313131313131313131 \
  -in input.txt | hexdump -C 
