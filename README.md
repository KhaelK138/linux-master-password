# Linux Master Password and Plaintext Password Logging

## Adding a Skeleton Key to Linux

Small script and C file for "backdooring" PAM and adding a master password ("master_password") to all users (similar to the functionality of Mimikatz's skeleton key). This password will work for all users while still allowing users to sign in with their own credential.

⚠️ **WARNING!!** ⚠️

Modifying PAM's `common-auth` file can very easily lock you (and everyone else) out of a system. If you modify the `common-auth` file first before transferring a valid `.so` binary to the location specified, you can (and will) brick system authentication. 

## Plaintext Password Logging

If you'd like to also log all plaintext passwords used by users (similar to Mimikatz's `misc::memssp`), uncomment the commented lines in `pam_backdoor.c` and `modify_common_auth.sh`.

## Installation

1) Compile the C code like so:

`gcc -fPIC -shared -o pam_login.so pam_backdoor.c`

2) ⚠️ Transfer the binary to `/etc/pam.d/` ⚠️ (this is important, pam will fail for new authentication attempts if it isn't present). 

3) Modify PAM's `common-auth` file by running `modify_common_auth.sh` on the target system. Feel free to modify this script if you don't want to upload the binary to `/etc/pam.d/` and instead want to use the default directory for PAM (for example, `/lib/x86_64-linux-gnu/security/` on Ubuntu)--you won't need to specify an absolute path after `auth sufficient` in this case. 

## Information

Naturally, this doesn't actually patch or recompile anything from PAM. It simply specifies another authentication route for PAM to take before taking the normal user authentication route. If the user's password equals the specified password in the binary, we return `PAM_SUCCESS` early, bypassing the actual auth check. If not, we default to the original auth check.

Running this source code on a machine that you are not allowed to access or modify is illegal. I'm not responsible for any damage intentionally or accidentally caused by use of this tool.
