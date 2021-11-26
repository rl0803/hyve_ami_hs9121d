#!/bin/bash

DEBUG=0
SILENT=1

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

INITRD_IMG_IN_PATH="$(cd "$(dirname "$1")"; pwd -P)/$(basename "$1")"
KEY_PATH="$(cd "$(dirname "$2")"; pwd -P)/$(basename "$2")"
INITRD_IMG_OUT_PATH="$(cd "$(dirname "$3")"; pwd -P)/$(basename "$3")"



#parameter check
if [ ! -f "$INITRD_IMG_IN_PATH" ]; then
    echo File $INITRD_IMG_IN_PATH does not exist.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo $INITRD_IMG_IN_PATH checked ok.; fi
if [ ! -f "$KEY_PATH" ]; then 
    echo File $KEY_PATH does not exist.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo $KEY_PATH checked ok.; fi

#encrypted check
# if [ "$(head -c 2 $INITRD_IMG_IN_PATH)" != "\x1f\x8b" ]; then
if [ "$(tail -c+65 $INITRD_IMG_IN_PATH|xxd -g2 -l2|awk '{print $2}')" != "1f8b" ]; then
    if [ $DEBUG -eq 1 ]; then echo echo $INITRD_IMG_IN_PATH appears to be encrypted. Attempting decrypt.; fi
    if [ $SILENT -eq 1 ]; then openssl enc -d -aes-256-cbc -nosalt -in $INITRD_IMG_IN_PATH -out $INITRD_IMG_IN_PATH -K "20191216" -iv "20191218" -p >/dev/null
    else openssl enc -d -aes-256-cbc -nosalt -in $INITRD_IMG_IN_PATH -out $INITRD_IMG_IN_PATH -K "20191216" -iv "20191218" -p
    fi
    if [ $? -ne 0 ]; then
        echo Openssl decrypt failed.
        exit 1
    fi
    if [ $DEBUG -eq 1 ]; then echo Decrypted ok.; fi
else
    if [ $DEBUG -eq 1 ]; then echo $INITRD_IMG_IN_PATH appears to be gzipped.; fi
fi

#get gzip portion of file
tail -c+65 < $INITRD_IMG_IN_PATH > $INITRD_IMG_IN_PATH.gz
if [ $? -ne 0 ]; then
    echo Creating $INITRD_IMG_IN_PATH.gz failed.
    exit 1
fi
if [ ! -f "$INITRD_IMG_IN_PATH.gz" ]; then
    echo $INITRD_IMG_IN_PATH.gz file does not exist.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Got gzippped portion ok.; fi

#save cd for later
CDSAVE=$(pwd)

#clear initrd working dir
if [ -d "initrd" ]; then
    if [ $SILENT -eq 1 ]; then rm -rf initrd >/dev/null 2>&1
    else rm -rf initrd
    fi
fi

#make initrd working dir
if [ $SILENT -eq 1 ]; then mkdir initrd >/dev/null 2>&1
else mkdir initrd
fi
if [ $? -ne 0 ]; then
    echo Failed creating initrd directory.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Made initrd dir ok.; fi

#cd to initrd working dir
cd initrd
if [ $? -ne 0 ]; then
    echo Failed changing directory to initrd directory.
    exit 1
fi
if [ "$(pwd)" != "$CDSAVE/initrd" ]; then
    echo Failed changing directory to initrd directory.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Cd to initrd directory ok.; fi

#ungzip and unpack
if [ $SILENT -eq 1 ]; then zcat $INITRD_IMG_IN_PATH.gz|cpio -idmv >/dev/null 2>&1
else zcat $INITRD_IMG_IN_PATH.gz|cpio -idmv
fi
if [ $? -ne 0 ]; then
    echo Zcat/cpio extraction failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Zcat/cpio extracted ok.; fi

#copy key into place
if [ $SILENT -eq 1 ]; then cp $KEY_PATH ./etc/key >/dev/null
else cp $KEY_PATH ./etc/key
fi
if [ $? -ne 0 ]; then
    echo Copying $KEY_PATH file failed
    exit 1
fi
#if [ -f "./etc/key" ]; then
#    echo $KEY_PATH file does not exist.
#    exit 1
#fi
if [ $DEBUG -eq 1 ]; then echo Key copied ok.; fi

#repack and gzip
find . | cpio -o -H newc 2>/dev/null | gzip > $INITRD_IMG_IN_PATH.new.gz
if [ $? -ne 0 ]; then
    echo Cpio/gzip packing failed.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo Cpio/gzip packed ok.; fi

#make image
if [ $SILENT -eq 1 ]; then mkimage -A arm -O linux -T ramdisk -C gzip -n "ARM Linux RAMDisk Image" -d $INITRD_IMG_IN_PATH.new.gz $INITRD_IMG_OUT_PATH >/dev/null
else mkimage -A arm -O linux -T ramdisk -C gzip -n "ARM Linux RAMDisk Image" -d $INITRD_IMG_IN_PATH.new.gz $INITRD_IMG_OUT_PATH
fi
if [ $? -ne 0 ]; then
    echo Failed making initrd image.
    exit 1
fi
if [ $DEBUG -eq 1 ]; then echo $INITRD_IMG_OUT_PATH created ok.; fi



cd $CDSAVE
#rm $INITRD_IMG_IN_PATH.gz
#rm $INITRD_IMG_IN_PATH.new.gz
#rm -r initrd