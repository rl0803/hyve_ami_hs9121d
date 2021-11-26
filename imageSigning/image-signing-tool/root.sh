#!/bin/bash

DEBUG=0
SILENT=1

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

ROOT_IMG_IN_PATH="$(cd "$(dirname "$1")"; pwd -P)/$(basename "$1")"
KEY_PATH="$(cd "$(dirname "$2")"; pwd -P)/$(basename "$2")"
ROOT_IMG_OUT_PATH="$(cd "$(dirname "$3")"; pwd -P)/$(basename "$3")"

#parameter check
if [ ! -f "$ROOT_IMG_IN_PATH" ]; then
    echo File $ROOT_IMG_IN_PATH does not exist.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo $ROOT_IMG_IN_PATH checked ok.; fi
if [ ! -f "$KEY_PATH" ]; then 
    echo File $KEY_PATH does not exist.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo $KEY_PATH checked ok.; fi

#create zeroed output file
ROOT_IMG_IN_SIZE=$(find "$ROOT_IMG_IN_PATH" -printf "%s")
ROOT_IMG_OUT_SIZE_M=$(($(($ROOT_IMG_IN_SIZE / 1000000)) + 1))
if [ $SILENT -eq 1 ]; then dd if=/dev/zero of=$ROOT_IMG_OUT_PATH bs=1M count=$ROOT_IMG_OUT_SIZE_M >/dev/null 2>&1
else dd if=/dev/zero of=$ROOT_IMG_OUT_PATH bs=1M count=$ROOT_IMG_OUT_SIZE_M
fi
if [ $? -ne 0 ]; then
    echo Creating zeroed output file failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Created zeroed output file ok.; fi

#create loop on output file
LOOP_DEVICE=$(losetup -f)
losetup $LOOP_DEVICE $ROOT_IMG_OUT_PATH
if [ $? -ne 0 ]; then
    echo Creating loop on output file failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Created loop on output file ok.; fi

#format with cryptsetup
if [ $SILENT -eq 1 ]; then cryptsetup -v -c aes-cbc-essiv:sha256 --batch-mode luksFormat $LOOP_DEVICE $KEY_PATH >/dev/null
else cryptsetup -v -c aes-cbc-essiv:sha256 --batch-mode luksFormat $LOOP_DEVICE $KEY_PATH
fi
if [ $? -ne 0 ]; then
    echo Formatting with cryptsetup failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Formatted with cryptsetup ok.; fi

#map device for writing
if [ $SILENT -eq 1 ]; then cryptsetup -c aes-cbc-essiv:sha256 --key-file=$KEY_PATH luksOpen $LOOP_DEVICE ee >/dev/null
else cryptsetup -c aes-cbc-essiv:sha256 --key-file=$KEY_PATH luksOpen $LOOP_DEVICE ee
fi
if [ $? -ne 0 ]; then
    echo Mapping device with cryptsetup failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Mapped device with cryptsetup ok.; fi

#write input image into mapped dev
if [ $SILENT -eq 1 ]; then dd if=$ROOT_IMG_IN_PATH of=/dev/mapper/ee >/dev/null 2>&1
else dd if=$ROOT_IMG_IN_PATH of=/dev/mapper/ee
fi
if [ $? -ne 0 ]; then
    echo Copying input image into mapped device failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Copied input image into mapped device ok.; fi

#unmap device
if [ $SILENT -eq 1 ]; then cryptsetup -c aes-cbc-essiv:sha256 luksClose ee >/dev/null
else cryptsetup -c aes-cbc-essiv:sha256 luksClose ee
fi
if [ $? -ne 0 ]; then
    echo Unmapping device failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Unmapped device ok.; fi

#free loop device
losetup -d $LOOP_DEVICE
if [ $? -ne 0 ]; then
    echo Freeing loop device failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Freed loop device ok.; fi

