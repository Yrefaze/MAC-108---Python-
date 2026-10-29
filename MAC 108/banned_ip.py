raw_log = "ALERT | 2026-10-19 | 192.168.4.11 | SQL_Injection_Attempt"
banned_ip = ('192.168.4.11')
user_input = input("Press 'Enter' to view the log report: ")
if user_input == "" :
 print(raw_log)
 print()
else:
 raw_log = user_input
print ("veryfing the IP address")
print(".")
print(".")
print(".")

ip = raw_log.split("|")[2]
new_ip = ip.strip()

if new_ip in banned_ip :
 print(ip ,"is a banned IP address! ")
else:
 print("no")

 