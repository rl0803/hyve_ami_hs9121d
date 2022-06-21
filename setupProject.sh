#!/bin/bash


### Common code Repos ###
AST2600_BRANCH="67968befdf22962a5a8985ed3dd7a1a9f90880c1"
BOOTLOADER_BRANCH="4373150b320357851e331878bf564b3accb43312"
COMMON_BRANCH="3538eecb03f133263ef9f3ad69c30ad846fff329"
HYVECOMMON_BRANCH="217d6a4ca807e1c28332180bb7175239f5b1370c"
KERNEL_BRANCH="81ce53500879433611c57c1e740bfb2213b621bb"
TARGET_BRANCH="6038f8055572fb3bd08b7ba359b8ff75df04c47c"
UTILITIES_VMCLI_BRANCH="c27499959ed52e51133875b035fc26d554c23e8d"


# The format of mapping table:
#       "submodule" "branch name / tag / commit hash ID "  "VarName" \
#
MappingList_submodule_branch=(\
    "packages/ast2600" "${AST2600_BRANCH}" "AST2600_BRANCH" \
    "packages/bootloader" "${BOOTLOADER_BRANCH}" "BOOTLOADER_BRANCH" \
    "packages/common" "${COMMON_BRANCH}" "COMMON_BRANCH" \
    "packages/hyvecommon" "${HYVECOMMON_BRANCH}" "HYVECOMMON_BRANCH" \
    "packages/kernel" "${KERNEL_BRANCH}" "KERNEL_BRANCH" \
    "packages/target" "${TARGET_BRANCH}" "TARGET_BRANCH" \
    "packages/vmcli" "${UTILITIES_VMCLI_BRANCH}" "UTILITIES_VMCLI_BRANCH" \
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
        if [ ${SHOW_COMMITID} -eq 0 ]; then
		    echo "Check submodule ${submodule} ..."
        fi

        for ((i=0;i<=${count_submodules};))
        do
            item=(${MappingList_submodule_branch[${i}]})

            if [ "${item}" == "${submodule}" ]; then
                brIndex=(${i}+1)
                branch=(${MappingList_submodule_branch[${brIndex}]})
                
                if [ ${SHOW_COMMITID} -eq 0 ]; then
                    echo "Find matched ${item}"
                    echo "Branch: ${branch}"
                fi
                
                cd ${submodule}

                if [ ${SHOW_COMMITID} -eq 1 ]; then
                    commitID=`git log | head -n 1 | cut -d ' ' -f 2`
                    
                    varNameIndex=(${i}+2)
                    varName=(${MappingList_submodule_branch[${varNameIndex}]})
                    echo -e "${varName}=\"${commitID}\""

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
            i=$((${i}+3))
        done
	fi
done < "${filename}"
