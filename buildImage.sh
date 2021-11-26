#!/bin/bash

PRJ_FILE="configs/ast2600evb_HS9121D_dev.PRJ"
UPDATEPRJ=""

if [ $# -gt 0 ]; then
    if [ "$1" == "-u" ]; then
        UPDATEPRJ="--updateprj"
        if [ -n "$2" ]; then
            PRJ_FILE=$2
        fi
    elif [ "$1" == "-h" ]; then
        echo -e "Usage: $0 [-u | -h] [PRJ file]\nE.g. $0 -u configs/ast2600evb_HS9121D_dev.PRJ"
        exit 0
    else
        PRJ_FILE=$1
    fi
fi

WORKSPACE="workspace/"

echo -e "Execute command:\n\tgit spx buildsrc ${UPDATEPRJ} ${PRJ_FILE} packages ${WORKSPACE}"

git spx buildsrc ${UPDATEPRJ} ${PRJ_FILE} packages ${WORKSPACE}

if [ $? -eq 0 ]; then
    $PWD/signImageGitSpx.sh
fi
