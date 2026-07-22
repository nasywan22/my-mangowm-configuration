#include "glib-object.h"
#include "glib.h"
#include "polkit/polkittypes.h"
#include <polkit/polkit.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_sudo_access.h"

void free_gobjects(
    PolkitAuthorizationResult *result,
    PolkitAuthority *authority,
    PolkitSubject *owner_identifier
)
{
    if (result != NULL) g_object_unref(result);
    if (authority != NULL) g_object_unref(authority);
    if (owner_identifier != NULL) g_object_unref(owner_identifier);
}

bool req_sudo_access()
{
    const char *action_id = "org.freedesktop.login1.reboot";
    GError *error = NULL;
    PolkitSubject *owner_identifier = polkit_unix_process_new_for_owner(getpid(), 0, -1);
    PolkitAuthority *authority = polkit_authority_get_sync(NULL, &error);
    PolkitAuthorizationResult *result = polkit_authority_check_authorization_sync(
        authority, 
        owner_identifier, 
        action_id, 
        NULL, 
        POLKIT_CHECK_AUTHORIZATION_FLAGS_ALLOW_USER_INTERACTION, 
        NULL, 
        &error
    );

    bool is_authorized = polkit_authorization_result_get_is_authorized(result);

    free_gobjects(result, authority, owner_identifier);

    return is_authorized;
}