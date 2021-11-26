#!/bin/bash

PRJ_FILE="configs/ast2600evb_HS9121D_dev.PRJ"

if [ $# -lt 1 ]; then
    echo "Usage: $0 [xxx.PRJ] <spx-package> or $0 <spx-package>"
    echo "E.g. $0 configs/ast2600evb_HS9121D_dev.PRJ libipmipdk-13.8.5.0.0-ARM-AST2600-AST2600EVB-AMI-src.spx"
    exit 1
fi

if [ $# -gt 1 ]; then
    PRJ_FILE=$1
    PACKAGE=$2
else
    PACKAGE=$1
fi


WORKSPACE="workspace/"

git spx buildsrc ${PRJ_FILE} packages ${WORKSPACE} ${PACKAGE}
