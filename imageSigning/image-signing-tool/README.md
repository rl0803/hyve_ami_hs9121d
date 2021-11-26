# ImageSigning Tool
This tool is used to embed public keys for secured boot, signed hashed image, backup and restore
configuration support and the corresponding encrypted hash to SPX firmware images

# Configuration File
Kindly use spx13_configuration.ini for SPX13 and configuration.ini for SPX12.

## ImageSigning Tool Options
ImageSigning Tool has below explained options via configuration file.

**Syntax**

```
./ImageSigningTool –ini <configuration file>
```

**Sample Configuration File**

```
[GLOBAL]
fwimagepath = rom.ima
Output = encrypted_rom.ima
overwrite_image = no
is_spx_image = yes

[SECURE_BOOT_SUPPORT]
publickey = Secure_boot_public_key.pem
privatekey = Secure_boot_private_key.pem
extended_uboot = no
include_uboot = no
hsm = yes
sign_script = extsign.sh

[SIGNED_HASHED_SUPPORT]
privatekey = Signed_Hash_private_key.pem
publickey = Signed_Hash_public_key.pem
hashtype = SHA256
hsm = yes
sign_script = extsign.sh
add_pub_key_only = no

[BACKUP_AND_RESTORE_KEY]
aeskey = path_to_key
aesiv = path_to_iv

# ImageSigning Tool
This tool is used to embed public keys for secured boot, signed hashed image, backup and restore
configuration support and the corresponding encrypted hash to SPX firmware images

## ImageSigning Tool Options
ImageSigning Tool has below explained options via configuration file.

**Syntax**

```
./ImageSigningTool –ini <configuration file>
```

**Sample Configuration File**

```
[GLOBAL]
fwimagepath = rom.ima
Output = encrypted_rom.ima
overwrite_image = no
is_spx_image = yes

[SECURE_BOOT_SUPPORT]
publickey = Secure_boot_public_key.pem
privatekey = Secure_boot_private_key.pem
extended_uboot = no
include_uboot = no
hsm = yes
sign_script = extsign.sh

[SIGNED_HASHED_SUPPORT]
privatekey = Signed_Hash_private_key.pem
publickey = Signed_Hash_public_key.pem
hashtype = SHA256
hsm = yes
sign_script = extsign.sh
add_pub_key_only = no

[BACKUP_AND_RESTORE_KEY]
aeskey = path_to_key
aesiv = path_to_iv

[SPL_SUPPORT]
version = a0
header_offset = 0x20
start_address = 0x0
image_size = 0x4000
sign_offset = 0x200
rev_hi = 0
rev_lo = 0
encryption = 1
aeskey1 = aeskey1.bin
aesiv1 = aesiv1.bin
aeskey2 = aeskey2.bin
aesiv2 = aesiv2.bin
aeskey3 = aeskey2.bin
rsakey1private = privkey.key
rsakey1public = pubkey.key
rsakey2private = privkey.key
rsakey2public = pubkey.key
spl_script =  extspl.sh

[SPL_BL2_IMAGE_SUPPORT]
header_offset = 0x20
load_address = 0x10000
image_len = 0x1000
verified_info_offset = 0x3c00
verify_method = signature
sign_script = extsign.sh
sign_location = 0x4200
rsa_mode = 2048
sha_mode = 256
privatekey = bl2_sign_private.key
publickey = bl2_sign_public.key
```

**Description**

**GLOBAL Section**  
- **fwimagepath** - This section holds the location of the input firmware image.   
- **Output** – Location of where signed images need to be generated.
- **overwrite_image** – This option specifies whether to overwrite existing output or not. The default setting is no.
- **spx_image** - This option specifies whether the input image is spx image or other image during signing. If the flag is not included in config file, then it will sign all the images as default. If the user wants to sign the other type of images rather than the spx images, then the flag is_spx_image should be included in config file and it should be set as "no".

**SECURE_BOOT_SUPPORT Section**  
This Section contains the essential informations for secure boot and extended secureboot support.

- **publickey**  - location of the public key in your build machine
- **privatekey** - location of the private key in your build machine
- **keyhandle** - String used by the HSM to identify the key. If the **keyhandle** is provided, **private key** should not be provided, and vice versa.
- **extended_uboot** - This option enables extended uboot hash generation. Separate hash for uboot and backup uboot will be calculated and stored in firmware info section. This can be used by the loader modules to validate the integrity of the uboot and backup uboot. This option is used only if the firmware has backup uboot.
- **include_uboot** - This option is to include UBOOT also for secure boot validation. This option is used only when include uboot option is enabled in PRJ.
Note: Secure Boot support only works with 2048 bit keys.
- **hsm** - This option specifies that the external signing script should use the HSM for signing.
- **sign_script** - This option indicates the name of the script file to be used for signing. The default is "extsign.sh".

**SIGNED_HASHED_SUPPORT Section**  
This Section contains essential information for appending Signed hash to the input image.
- **publickey** - location of the public key in your build machine
- **privatekey** -  location of the private key in your build machine
- **keyhandle** - String used by the HSM to identify the key. If the **keyhandle** is provided, **private key** should not be provided, and vice versa.
- **Hash type** -  This option accepts following algorithms: SHA1, SHA224, SHA256, SHA512 and SHA384.
- **hsm** - This option specifies that the external signing script should use the HSM for signing.
- **sign_script** - This option indicates the name of the script file to be used for signing. The default is "extsign.sh".
- **add_pub_key_only** - This option specifies whether to add only public key or to go for signed hash support. The default setting is no.

**BACKUP_AND_RESTORE_KEY Section**  
This Section contains essential information for embedding AES KEY and AES IV to the input image.

- **aeskey** - location of the AES key in your build machine
- **aesiv** - location of the AES IV in your build machine

# Note
PLEASE MAKE SURE TO GIVE THE EXECUTE PERMISSION TO THE SCRIPT IF WE WANT TO RUN CONFIGURATION FILE WHICH CONTAINS SIGN_SCRIPT FIELD IN ANY OF THESE TWO SECTION SECURE_BOOT_SUPPORT/SIGNED_HASHED_SUPPORT. FOR EXAMPLE : HERE WE HAVE TO GIVE EXECUTE PERMISSION TO EXTSIGN.SH SCRIPT AND THEN RUN IMAGESIGNINGTOOL WITH THE CONFIGURATION FILE.





```

**Description**

**GLOBAL Section**  
- **fwimagepath** - This section holds the location of the input firmware image.   
- **Output** – Location of where signed images need to be generated.
- **overwrite_image** – This option specifies whether to overwrite existing output or not. The default setting is no.
- **spx_image** - This option specifies whether the input image is spx image or other image during signing. If the flag is not included in config file, then it will sign all the images as default. If the user wants to sign the other type of images rather than the spx images, then the flag is_spx_image should be included in config file and it should be set as "no".

**SECURE_BOOT_SUPPORT Section**  
This Section contains the essential informations for secure boot and extended secureboot support.

- **publickey**  - location of the public key in your build machine
- **privatekey** - location of the private key in your build machine
- **keyhandle** - String used by the HSM to identify the key. If the **keyhandle** is provided, **private key** should not be provided, and vice versa.
- **extended_uboot** - This option enables extended uboot hash generation. Separate hash for uboot and backup uboot will be calculated and stored in firmware info section. This can be used by the loader modules to validate the integrity of the uboot and backup uboot. This option is used only if the firmware has backup uboot.
- **include_uboot** - This option is to include UBOOT also for secure boot validation. This option is used only when include uboot option is enabled in PRJ.
Note: Secure Boot support only works with 2048 bit keys.
- **hsm** - This option specifies that the external signing script should use the HSM for signing.
- **sign_script** - This option indicates the name of the script file to be used for signing. The default is "extsign.sh".

**SIGNED_HASHED_SUPPORT Section**  
This Section contains essential information for appending Signed hash to the input image.
- **publickey** - location of the public key in your build machine
- **privatekey** -  location of the private key in your build machine
- **keyhandle** - String used by the HSM to identify the key. If the **keyhandle** is provided, **private key** should not be provided, and vice versa.
- **Hash type** -  This option accepts following algorithms: SHA1, SHA224, SHA256, SHA512 and SHA384.
- **hsm** - This option specifies that the external signing script should use the HSM for signing.
- **sign_script** - This option indicates the name of the script file to be used for signing. The default is "extsign.sh".
- **add_pub_key_only** - This option specifies whether to add only public key or to go for signed hash support. The default setting is no.

**BACKUP_AND_RESTORE_KEY Section**  
This Section contains essential information for embedding AES KEY and AES IV to the input image.

- **aeskey** - location of the AES key in your build machine
- **aesiv** - location of the AES IV in your build machine

**SPL_SUPPORT Section**
This section contains essential information for determining the header type (A0 or A1) and for setting up Secure Boot encryption.  It can be omitted if not desired.
- **version** - The type of secure boot header.  Either **a0** or **a1**.  Defaults to **a0** if not included.
- **header_offset** - The header offset.  Defaults to **0x20** if not included.
- **start_address** - The start address of the image.  Defaults to **0x0** if not included.
- **image_size** - The size of the image.  Defaults to **0x4000** if not included.
- **sign_offset** - The offset to the signature location.  Defaults to **0x200** if not included.
- **rev_hi** - The high word of the header revision.  Defaults to **0x0** if not included.
- **rev_lo** - The low word of the header revision.  Defaults to **0x0** if not included.
- **encryption** - Switch to enable Secure Boot Encryption.  Valid settings are **0** (disabled) and **1** (enabled).
- **aeskey1** - The name of the file containing AES key 1.  This key is used to encrypt SPL image.  This setting is ignored if **encryption** is **0**.
- **aesiv1** - The name of the file containing the IV to use with AES key 1.  This setting is ignored if **encryption** is **0**.
- **aeskey2** - The name of the file containing AES key 2.  This key is used to encrypt Kernel and Initrd modules.  This setting is ignored if **encryption** is **0**.
- **aesiv2** - The name of the file containing the IV to use with AES key 2.  This setting is ignored if **encryption** is **0**.
- **aeskey3** - The name of the file containing AES key 3.  This key is used with cryptsetup to encrypt the root module.  This setting is ignored if **encryption** is **0**.
- **rsakey1private** - The name of the file containing RSA key 1 private portion.  This is used to sign the encrypted SPL image, and the unencrypted U-boot image.  This setting is ignored if **encryption** is **0**.
- **rsakey1public** - The name of the file containing RSA key 1 public portion  This setting is ignored if **encryption** is **0**.
- **rsakey2private** - The name of the file containing RSA key 2 private portion.  This is used to sign all encrypted modules.  This setting is ignored if **encryption** is **0**.
- **rsakey2public** - The name of the file containing RSA key 2 public portion.  This setting is ignored if **encryption** is **0**.

**SPL_BL2_IMAGE_SUPPORT section**
This section contains essential information for describing and signing the BL2.  It can be omitted if not desired, but requires **SPL_SUPPORT** section if **SPL_BL2_IMAGE_SUPPORT** is included.
- **header_offset** - The BL2 header offset.  Defaults to **0x20** if not included.
- **load_address** - The load address.  Defaults to **0x10000** if not included.
- **image_len** - The length of the image.  Defaults to **0x1000** if not included.
- **verified_info_offset** - Offset to U-boot signature.  Defaults to **0x3c00** if not included.
- **verify_method** - The verification method.  Valid values are **signature** and **hash_binding**.
- **sign_script** - The file name of the external signing script to use.  Defaults to **extsign.sh** if not included.
- **sign_location** - Offset to SPL signature.  Defaults to **0x4200** if not included.
- **rsa_mode** - The RSA key size, in bits.  Valid values are **1024**, **2048**, **3072**, and **4096**.
- **sha_mode** - The SHA algorithm to use.  Valid values are **224**, **256**, **284**, and **512**.
- **privatekey** - The file name of the RSA private key to use for signing BL2 image.  Defaults to **bl2_sign_private.key** if not included.
- **publickey** - The filename of the public key corresponding to the private key.  Defaults to **bl2_sign_public.key** if not included.


# Note
PLEASE MAKE SURE TO GIVE THE EXECUTE PERMISSION TO THE SCRIPT IF WE WANT TO RUN CONFIGURATION FILE WHICH CONTAINS SIGN_SCRIPT FIELD IN ANY OF THESE TWO SECTION SECURE_BOOT_SUPPORT/SIGNED_HASHED_SUPPORT. FOR EXAMPLE : HERE WE HAVE TO GIVE EXECUTE PERMISSION TO EXTSIGN.SH SCRIPT AND THEN RUN IMAGESIGNINGTOOL WITH THE CONFIGURATION FILE.




