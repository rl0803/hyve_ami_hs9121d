# Project HS9121D

## Clone & setup this repos:
    ~# git clone --recurse-submodules https://bitbucket.hyvedesignsolutions.com/scm/h13/hs9121d.git
    ~# cd hs9121d
    ~# ./setupProject.sh

## The layout of this repos

        |---configs
        |
        |---packages
        |    |
        |    ---ast2600             ---> a common code submodule
        |    |
        |    ---bootloader          ---> a common code submodule
        |    |
        |    ---common              ---> a common code submodule
        |    |
        |    ---kernel              ---> a common code submodule
        |    |
        |    ---target              ---> a common code submodule
        |    |
        |    ---utilities           ---> a common code submodule
        |    |
        |    |
        |    ---hyvecommon          ---> a common code submodule
        |    |    |
        |    |    --- libhyvecommon-src
        |    |    |
        |    |    --- hyvecommon_dev-src
        |    |    |
        |    |    --- Hyve_Features-ANY
        |    |    |
        |    |    --- overrides       ---> to override the AMI submodules
        |    |    |
        |    |    --- ...
        |    |
        |    |
        |    ---project             ---> the platform code
        |       |
        |       --- hyveplatform_dev-src
        |       |
        |       --- overrides       ---> to override the hyvecommon submodule or the AMI submodules
        |       |
        |       --- ...
        |
        |
        |---Hyve_ddf
        |
        |---ImageSigning
            |
            |---GenerateKey.sh
            |
            |---image-signing-tool
            |
            |---key
            |
            |---README.md
            |
            |---RomImage.py_MDS13.3.patch
            |---RomImage.py_MDS13.2.1.patch


## About version control of each submodule:
- Please modify the variables of the script, to choose your favorite.
  For example:

      AST2600_BRANCH="hyvecommon_dev"
      BOOTLOADER_BRANCH="hyvecommon_dev"
      COMMON_BRANCH="hyvecommon_dev"
      HYVECOMMON_BRANCH="hyvecommon_dev"
      KERNEL_BRANCH="hyvecommon_dev"
      TARGET_BRANCH="e6de1366e4cb054171b3b7ac95ce81a576d9302b"
      UTILITIES_VMCLI_BRANCH="hyvecommon_dev"

## Requirements:
- Get and install the latest released **Git SPX Plugin** version (version **v1.0-beta8.5** or **later**)
  
  The URL: https://git.ami.com.tw/tools/git-spx-plugin/releases

- Get and install the latest released MDS version (version **13.3** or **later**)
  
  The URL: https://git.ami.com.tw/tools/mds/releases

- Note:
  Because AMI has changed the kernel image name from **uImage** to **kernel_fit** and also the firmware image layout since **MDS version 13.3** and **Git SPX Plugin version ???**.


## Important Information
- The build rule of packages (**the "override" mechanisum**):
    1. The git-spx uses package version to determine which package should be used for compiling,
    if it finds duplicate package name.
    For example, if the ipmipdk_dev-src both found in packages/common/packages/ and in packages/overrides/packages/,
    the version in common is 13.2.0.0.0 and the other one in overrides is 13.2.0.1.0
    then the git-spx will choose the higher one.

- Limitation of git-spx:
    1. The **git-spx** cannot allow using soft-link for packages, it must be a physical link.
    2. Cannot use "platform" for packages folder name, so we use "project" instead.

- When you use **git-spx** build a project, it will create a folder **spx-packages-links** which has soft-links linked to corresponding packages, and the every package of the **source** folder links to it.
Your modification will be taken effect directly of the **packages**.


        root@alan-desktop:~/AMI_RR13_LTS/HS9121# ls -lh spx-packages-links/adcapp-13.1.1.0.0-src.spx
        lrwxrwxrwx 1 root root 73 Jul 30 10:39 spx-packages-links/adcapp-13.1.1.0.0-src.spx -> ~/AMI_RR13_LTS/HS9121/packages/common/packages/adcapp-src

        root@alan-desktop:~/AMI_RR13_LTS/HS9121# ls -lh workspace/source/adcapp-13.1.1.0.0-src/total 8.0K
        lrwxrwxrwx 1 root root 87 Jul 30 10:52 data -> ~/AMI_RR13_LTS/HS9121/spx-packages-links/adcapp-13.1.1.0.0-src.spx/data
        lrwxrwxrwx 1 root root 86 Jul 30 10:52 spx -> ~/AMI_RR13_LTS/HS9121/spx-packages-links/adcapp-13.1.1.0.0-src.spx/spx



## Steps for compilation

#### Using Git SPX Plugin

    ~# git spx buildsrc --updateprj configs/xxx.PRJ packages/ workspace

#### Note:
- To support image-signning, after you build the project with git-spx.

  Please rember run the script **signImageGitSpx.sh** to sign your BMC image.

      ~# ./signImageGitSpx.sh

#### The **buildImage.sh**
- This script wraps the "git spx buildsrc" cmd and the "signImageGitSpx.sh".

- It's recommand to run this script to build this project.

      ~# ./buildImage.sh

- Note: Due to the new version of git-spx for using new image layout has not been released yet, so use MDSv13.3 instead. 

#### The **buildSinglePackage.sh**
- This script wraps the "git spx buildsrc" cmd to build a single package

      ~# ./buildSinglePackage.sh <xxx.PRJ> <spx-package>

- You can find the package in the **spx-packages-links** folder.
  e.g.

        ~# ls spx-packages-links/ | grep libipmipdk
        libipmipdk-13.3.1.0.0-src.spx
        libipmipdk-13.8.5.0.0-ARM-AST2600-AST2600EVB-AMI-src.spx
        libipmipdkapi-13.1.1.0.0-src.spx
        libipmipdkcmds-13.0.0.0.0-ARM-AST2600-AST2600EVB-AMI-src.spx
        libipmipdkcmds-13.0.0.0.0-src.spx

        ~# ./buildSinglePackage.sh configs/ast2600evb_HS9121D_dev.PRJ libipmipdk-13.8.5.0.0-ARM-AST2600-AST2600EVB-AMI-src.spx


#### Using MDS

- Step 1. Converts packages to ".spx" format

	    ~# git spx convert packages/ spx-packages/

- Step 2. Create a SPX project with the **spx-packages** and the **workspace** in MDS

#### Note:
- If you using MDS to do your work, please remember to sync your change to the **packages** folder.

