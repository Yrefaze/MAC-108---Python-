import json
raw_data = b'{"data": {"username": "jdoe", "is_active": true}}'


json_str = raw_data.decode("utf-8")
data = json.loads(json_str)

print(data["data"]["username"])
print(data["data"]["is_active"])