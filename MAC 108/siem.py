# ==================================================
#  SIEM Dashboard Parser
#  MAC180 - Week 8, Day 2 Team Lab
#  Team: ______________________
# ==================================================

# ---- The login data our SIEM gave us ----
# Each user ID (like 'user_001') points to a smaller dictionary
# that holds that one user's info.
siem_logs = {
    'user_001': {'username': 'jdoe', 'status': 'active', 'failed_attempts': 1},
    'user_002': {'username': 'rsmith', 'status': 'locked', 'failed_attempts': 15},
    'user_003': {'username': 'tjones', 'status': 'active', 'failed_attempts': 0},
    'user_004': {
        'username': 'bwayne',
        'status': 'active'  # Note: 'failed_attempts' key missing!
    }
}

# Our security rule: MORE than this many failed logins = brute-force attack.
# Keeping it in one variable means we only change one line if the rule changes.
MAX_FAILED_LOGINS = 5


# ==================================================
#  TASK 1: Find brute-force attacks and lock those accounts
# ==================================================
# .items() hands us TWO things each time through the loop:
#   user_id   -> the outer key, like 'user_002'
#   user_info -> the inner dictionary with that user's details
for user_id, user_info in siem_logs.items():

    # .get() is the SAFE way to read a key.
    # If 'failed_attempts' is missing (like bwayne), we get 0 instead of a crash.
    failed_logins = user_info.get('failed_attempts', 0)

    if failed_logins > MAX_FAILED_LOGINS:
        # Changing user_info also changes siem_logs, because they are the same dictionary.
        user_info['status'] = 'locked'

        username = user_info.get('username', 'unknown')
        print(f"[CRITICAL] Account locked for user: {username}")


# ==================================================
#  TASK 2: Add the 2FA security flag to every user
# ==================================================
# .values() hands us ONLY the inner dictionaries.
# We skip the user IDs here because EVERY user gets the same flag.
for user_info in siem_logs.values():
    user_info['2FA_enabled'] = True  # the key doesn't exist yet, so Python creates it


# ==================================================
#  TASK 3: Print the final audit report
# ==================================================
# Back to .items(), because the report needs the user ID too.
for user_id, user_info in siem_logs.items():
    username = user_info.get('username', 'unknown')
    status = user_info.get('status', 'unknown')
    has_2fa = user_info.get('2FA_enabled', False)

    print(f"Audit Complete - ID: {user_id} | Username: {username} | Status: {status} | 2FA: {has_2fa}")