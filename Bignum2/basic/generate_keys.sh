#!/bin/bash

keydir=$PWD
keyfile="$keydir/keys/rsa_key"

# Generate public key file 
ssh-keygen -t rsa -b 2048 -f $keyfile

ssh-keygen -t rsa -b 2048 -f $keyfile -e -m pem > "$keydir/keys/rsa_public.pem"
cp -rf "$keydir/keys/rsa_key" "$keydir/keys/rsa_private.pem"

rm -rf "$keydir/keys/rsa_key"
rm -rf "$keydir/keys/rsa_key.pub"
