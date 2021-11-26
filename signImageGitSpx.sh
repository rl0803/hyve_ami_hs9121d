#!/bin/bash

WORKSPACE="${PWD}/workspace"

if [ $# -gt 0 ]; then
    WORKSPACE="$1"
fi

SIGNTOOL_DIR_copy="${WORKSPACE}/Build/output/image-signing-tool"
KEY_DIR_copy="${WORKSPACE}/Build/output/key"
ROM_IMA="${WORKSPACE}/Build/output/rom.ima"
ENCRYPT_IMA="${WORKSPACE}/Build/output/encrypted_rom.ima"
ENCRYPT_IMA_ENC="${WORKSPACE}/Build/output/encrypted_rom.ima_enc"

SIGNTOOL_DIR="${PWD}/imageSigning/image-signing-tool/"
KEY_DIR="${PWD}/imageSigning/key"

# Check rom.ima exist
if [ ! -e ${ROM_IMA} ]; then
    echo "${ROM_IMA}    NOT FOUND!"
    exit 1
fi

# Check sign tool exist
if [ ! -e ${SIGNTOOL_DIR} ]; then
    echo "${SIGNTOOL_DIR}    NOT FOUND!"
    exit 1
fi
# Check key exist
if [ ! -e ${KEY_DIR} ]; then
    echo "${KEY_DIR}    NOT FOUND!"
    exit 1
fi

# Copy sign tool and key to Build/output
if [ ! -e ${SIGNTOOL_DIR_copy} ]; then
    rm -rf ${SIGNTOOL_DIR_copy}
    cp -arfp ${SIGNTOOL_DIR} ${SIGNTOOL_DIR_copy}
fi
if [ ! -e ${KEY_DIR_copy} ]; then
    cp -arfp ${KEY_DIR} ${KEY_DIR_copy}
fi
# Remove previous images
if [ -e ${ENCRYPT_IMA} ]; then
    rm ${ENCRYPT_IMA}
fi
if [ -e ${ENCRYPT_IMA_ENC} ]; then
    rm ${ENCRYPT_IMA_ENC}
fi

cd ${SIGNTOOL_DIR_copy}
./imageSigningTool.sh

if [ $? -eq 0 ]; then
    echo -e "Outout Images:\n\t${ENCRYPT_IMA}\n\t${ENCRYPT_IMA_ENC}"
fi

