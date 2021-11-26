# Install image-signing-tool to MDS

- Step 1. Run the GenerateKey.sh to generate an uniue pair of key of your project.

- Step 2. Choose/create your 'image signning configuration.ini' file and write the file name to **imageSignConfig** file.
    For example:
        ~# echo "configuration_simpleSignedImageSupport.ini" > imageSignConfig
        ~# cat imageSignConfig

- Step 3. Copy the **image-signing-tool** folder to your MDS BuildPRJ folder.
    
        e.g.
        ~# cp -arfp ./image-signing-tool ~/MDS13.3/Linux/x86_64/MDS/spx/utils/BuildPRJ/

- Step 4. Copy the **key** folder to ..../utils/BuildPRJ/image-signing-tool/

        e.g.
        ~# cp -r ./key  ~/MDS13.3/Linux/x86_64/MDS/spx/utils/BuildPRJ/image-signing-tool/


## Note:
    If you change key or configuration.ini file, please also sync the change to the MDS.


- Step 5. Patch the **RomImage.py**
    If you are using **MDS version 13.2.1** or under this version, please use the **RomImage.py_MDS13.2.1.patch** file.
    If you are using **MDS version 13.2.1** or later version, please use the **RomImage.py_MDS13.3.patch** file.

        e.g.
        ~# cp ./RomImage.py_MDS13.3.patch ~/MDS13.3/Linux/x86_64/MDS/spx/utils/BuildPRJ/
        ~# patch -p0 < RomImage.py_MDS13.3.patch

