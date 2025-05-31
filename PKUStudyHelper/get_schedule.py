import sys
import json
from course import course 

def main():
    if len(sys.argv) < 3:
        print(json.dumps({"error": "请提供账号和密码"}))
        return

    account = sys.argv[1]
    password = sys.argv[2]

    try:
        c =Portal(account, password, verify=False)
        data = c.get_schedule()  
        print(json.dumps(data, ensure_ascii=False))  
    except Exception as e:
        print(json.dumps({"error": str(e)}))

if __name__ == "__main__":
    main()
