#!/bin/bash

openssl genrsa -out key/privatekey.pem 2048
openssl rsa -in key/privatekey.pem -pubout > key/publickey.pem

# openssl genrsa -out privatekey.pem
# openssl rsa -in privatekey.pem -pubout > publickey.pem