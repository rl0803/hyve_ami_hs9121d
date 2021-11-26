#!/bin/bash

var="$0"
TOOL_DIR=${var%'imageSigningTool.sh'*}
CONFIGFILE="${TOOL_DIR}imageSignConfig"
initConfig=`cat ${CONFIGFILE}`
CMD="${TOOL_DIR}ImageSigningTool -ini ${TOOL_DIR}${initConfig}"

echo "Execute ${CMD}"
${CMD}

exit $?


