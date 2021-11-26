#!/bin/bash


### Common code Repos ###
# AMI active branch for end-user: LTS-v13
#
# Last update date: 2021-09-13
#
# TARGET_BRANCH="cf083c0039a67146770f757a636f894ed069e206"
# COMMON_BRANCH="d66ae0939f5d9d35012cc81a308021c29c68626f"
# AST2600_BRANCH="e6dbe3605df8b41844575f564c5d0f2fa4bd83e1"
# KERNEL_BRANCH="7f4bff200e8bbc01977aac2bd7c1ae00567e2c6c"
# BOOTLOADER_BRANCH="559820080ad71b9b4c8f6cf54d5be6afbc008386"
TARGET_BRANCH="LTS-v13"
COMMON_BRANCH="LTS-v13"
AST2600_BRANCH="LTS-v13"
KERNEL_BRANCH="LTS-v13"
BOOTLOADER_BRANCH="LTS-v13"
UTILITIES_VMCLI_BRANCH="LTS-v13"


# The format of mapping table:
#       "submodule" "branch name / tag / commit hash ID " \
#
MappingList_submodule_branch=(\
    "packages/target" "${TARGET_BRANCH}" \
    "packages/common" "${COMMON_BRANCH}" \
    "packages/ast2600" "${AST2600_BRANCH}" \
    "packages/kernel" "${KERNEL_BRANCH}" \
    "packages/bootloader" "${BOOTLOADER_BRANCH}" \
    "packages/utilities/packages/vmcli" "${UTILITIES_VMCLI_BRANCH}" \
)

FORCE_RESET=0
if [ "$1" == "-f" ];then
    FORCE_RESET=1
fi

SHOW_COMMITID=0
if [ "$1" == "-s" ];then
    SHOW_COMMITID=1
fi

ROOT_DIR=${PWD}

# Checkout each sub-modules for common code
count_submodules=${#MappingList_submodule_branch[@]}
filename="${ROOT_DIR}/.gitmodules"

while read line;
do
	if echo ${line} | grep -q 'submodule' ; then
		submodule=`echo ${line} | cut -d '"' -f 2`
		echo "Check submodule ${submodule} ..."
        for ((i=0;i<=${count_submodules};))
        do
            item=(${MappingList_submodule_branch[${i}]})

            if [ "${item}" == "${submodule}" ]; then
                brIndex=(${i}+1)
                branch=(${MappingList_submodule_branch[${brIndex}]})
                echo "Find matched ${item}"
                echo "Branch: ${branch}"

                cd ${submodule}

                if [ ${SHOW_COMMITID} -eq 1 ]; then
                    commitID=`git log | head -n 1 | cut -d ' ' -f 2`
                    echo ${commitID}
                    cd ${ROOT_DIR}
                    break
                fi

                git checkout ${branch}
                if [ $? -ne 0 ]; then
                    echo "Fail to git checkout ${branch}..."
                    exit 1
                fi

                RES=`git pull 2>&1 | grep "Aborting"`
                if [ $? -eq 0 ]; then 
                    if [ ${FORCE_RESET} -eq 1 ]; then
                        # Force Reset
                        git unstage; git reset --hard
                        RES=`git pull 2>&1 | grep "Aborting"`
                        if [ $? -eq 0 ]; then
                            echo "Fail to git pull ${submodule}..."
                            exit 1
                        fi
                    else
                        echo "Fail to git pull ${submodule}..."
                        exit 1
                    fi
                fi

                git lfs pull
                if [ $? -ne 0 ]; then
                    echo "Fail to git lfs pull ${submodule}..."
                    exit 1
                fi
                echo "Ok!"
                cd ${ROOT_DIR}
                break
            fi
            i=$((${i}+2))
        done
	fi
done < "${filename}"
