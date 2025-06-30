# -*- coding: utf-8 -*-
'''
使用示例：
c = Course('学号', '密码', verify=False(若需要))
c.get_all_classes()  # 获取所有课程名和链接
p = Portal('学号', '密码', verify=False(若需要))
c.get_schedule()  # 获取课表
c.get_GPA()  # 获取GPA
c.deepseek('问题')  # 使用门户的 DeepSeek 功能
'''
import requests
import random
from urllib3.exceptions import InsecureRequestWarning
import json
from bs4 import BeautifulSoup
from datetime import datetime, time, timedelta
import re
from typing import Optional
import sys

# 禁用所有 InsecureRequestWarning 警告
requests.packages.urllib3.disable_warnings(category=InsecureRequestWarning)

class Course:
    '''
    教学网类。提供登录教学网、获取教学网上课程名、日程表等功能
    待开发：获取课程作业、公告、文件等功能；获取个人成绩；......
    '''

    headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36",
    "Accept-Encoding": "gzip, deflate, br, zstd",
    "Accept-Language": "zh-CN,zh;q=0.9",
    "Connection": "keep-alive"
    }
    def __init__(self, stu_id: str, password: str, verify: bool = True):
        '''
        初始化 Course 类，进行登录操作
        :param stu_id: 学号
        :param password: 密码
        :param verify: 是否验证 SSL 证书，默认为 True
        '''
        self.verify = verify
        self.stu_id = stu_id
        self.password = password
        self.session = requests.Session()
        self.session.headers.update(self.headers)
        self.login()

    def login(self) -> None:
        '''
        登录到教学网
        '''
        req1 = self.session.get("https://course.pku.edu.cn" ,verify=self.verify)
        req2 = self.session.get("https://course.pku.edu.cn/webapps/bb-sso-BBLEARN/login.html", verify=self.verify)
        submit_url = "https://iaaa.pku.edu.cn/iaaa/oauth.jsp"
        # 表单参数（从页面 JavaScript 中提取）
        data = {
            "appID": "blackboard",
            "appName": "1",
            "redirectUrl": "http://course.pku.edu.cn/webapps/bb-sso-BBLEARN/execute/authValidate/campusLogin"
        }
        # 提交 POST 请求（允许自动重定向）
        req3 = self.session.post(submit_url, data=data, allow_redirects=True, verify=self.verify)

        data = {
            "appid": "blackboard",
            "userName": self.stu_id,
            "password": self.password,
            "randCode": "",
            "smsCode": "",
            "otpCode": "",
            "redirUrl": "http://course.pku.edu.cn/webapps/bb-sso-BBLEARN/execute/authValidate/campusLogin"
        }
        req4 = self.session.post("https://iaaa.pku.edu.cn/iaaa/oauthlogin.do",
                                 data=data, allow_redirects=True, verify=self.verify)
        j = req4.json()
        if 'success' not in j or not j['success']:
            raise ValueError("Login failed, please check your student ID and password.")
        if 'token' not in j:
            raise ValueError("Login failed, token not found in response.")

        token = req4.json()["token"]

        data = {
            "rand": random.random(),
            "token": token
        }

        req5 = self.session.get("https://course.pku.edu.cn/webapps/bb-sso-BBLEARN/execute/authValidate/campusLogin", 
                                params=data, allow_redirects=True, verify=self.verify)


    def get_all_classes(self) -> dict[int, tuple[str, str]]:
        '''
        获取教学网上的所有课程名和链接（链接待以后开发其他功能时使用）
        :return: 一个字典，键为课程索引，值为一个元组，包含课程名和链接
        '''
        req = self.session.get("https://course.pku.edu.cn/webapps/portal/execute/tabs/tabAction?tab_tab_group_id=_1_1",
                                allow_redirects=True, verify=self.verify)
        if req.history: # 被重定向了，说明登录过期
            self.login()
            return self.get_all_classes()
        
        html = req.text
        soup = BeautifulSoup(html, 'html.parser')
        ul = soup.select_one('#\\$fixedId > div > div > ul')

        if ul:
            all_links = []
            names = []
            for li in ul.find_all('li'):
                a_tag = li.find('a')
                if a_tag:
                    all_links.append(a_tag)
                    raw_text = a_tag.get_text(strip=True)
                    f = raw_text.find(':')
                    r = raw_text.rfind('(')
                    if f!=-1 and r!=-1:
                        names.append(raw_text[f+1:r].strip())
                    else:
                        names.append(raw_text)
            n = len(names)
            res = {i:(names[i],'https://course.pku.edu.cn'+all_links[i]['href']) for i in range(n)}
            return res
        else:
            return []
        
    def _get_timestamp(self, yyyymmdd:str) -> int:
        """
        获取本地时区0点的毫秒级时间戳，查看教学网日程时使用
        :param yyyymmdd: 日期字符串，格式为 yyyymmdd (例如 20250601)
        :return: 本地时区0点的毫秒级时间戳
        """
        if not re.match(r'^\d{8}$', yyyymmdd):
            raise ValueError("日期格式必须为 yyyymmdd (例如 20250601)")
        year = int(yyyymmdd[:4])
        month = int(yyyymmdd[4:6])
        day = int(yyyymmdd[6:8])
        date_obj = datetime(year, month, day).date()
        midnight_local = datetime.combine(date_obj, time(0, 0, 0))
        return int(midnight_local.timestamp() * 1000)
    
    def get_timetable(self, start_date:Optional[str], end_date:Optional[str]) -> list[dict[str,str]]:
        '''
        获取教学网上的日程表
        :param start_date: 起始日期，格式为 yyyymmdd (例如 20250601)，如果为 None，则默认为今天
        :param end_date: 结束日期，格式为 yyyymmdd (例如 20250701)，如果为 None，则默认为起始日期后一个月
        时间是左闭右开的，查询的日程表不含end_date当天的日程，例如查询2025年6月的日程，则start_date='20250601',end_date='20250701'
        :return: 一个列表，每个元素是一个字典：{'time': '时间', 'title': '标题', 'link': '链接'}
        时间的格式：'2025-06-08T23:59:00'
        '''
        if start_date is None:
            start_date = datetime.now().strftime('%Y%m%d')
        if end_date is None:
            end_date = (datetime.now() + timedelta(days=30)).strftime('%Y%m%d')
        
        start_timestamp = self._get_timestamp(start_date)
        end_timestamp = self._get_timestamp(end_date)

        params = {
            'start': str(start_timestamp),
            'end': str(end_timestamp),
            'course_id': '',
            'mode': 'personal'
        }

        req = self.session.get("https://course.pku.edu.cn/webapps/calendar/calendarData/selectedCalendarEvents",
                               params=params, allow_redirects=True, verify=self.verify)
        if req.status_code != 200:
            self.login()
            return self.get_timetable(start_date, end_date)
        res = []
        j = req.json()
        for element in j:
            res.append({
                'time': element['start'],
                'title': element['title'],
            })
            r = self.session.get(f"https://course.pku.edu.cn/webapps/calendar/launch/attempt/{element['id']}",
                                 verify=self.verify, allow_redirects=True)
            res[-1]['url'] = r.url
        
        return res

class Portal:
    '''
    门户类。提供登录门户、获取课表、GPA、使用门户deepseek等功能
    '''
    def __init__(self, stu_id: str, password: str, verify: bool = True):
        '''
        初始化 Portal 类，进行登录操作
        :param stu_id: 学号
        :param password: 密码
        :param verify: 是否验证 SSL 证书，默认为 True
        '''
        self.verify = verify
        self.stu_id = stu_id
        self.password = password
        self.session = requests.Session()
        self.session.headers.update(Course.headers)
        self.login()

    def login(self) -> None:
        '''
        登录到门户
        '''
        req1 = self.session.get("https://portal.pku.edu.cn/portal2017", verify=self.verify)
        req2 = self.session.get("https://portal.pku.edu.cn/portal2017/login.jsp", verify=self.verify)
        submit_url = "https://iaaa.pku.edu.cn/iaaa/oauth.jsp?" 
        req3 = self.session.get(submit_url, params={
            "appID": "portal2017",
            "appName": "北京大学校内信息门户新版",
            "redirectUrl": "https://portal.pku.edu.cn/portal2017/ssoLogin.do"
        }, allow_redirects=True, verify=self.verify)

        data = {
            "appid": "portal2017",
            "userName": self.stu_id,
            "password": self.password,
            "randCode": "",
            "smsCode": "",
            "otpCode": "",
            "redirUrl": "https://portal.pku.edu.cn/portal2017/ssoLogin.do"
        }
        req4 = self.session.post("https://iaaa.pku.edu.cn/iaaa/oauthlogin.do",
                                 data=data, allow_redirects=True, verify=self.verify)
        j = req4.json()
        if 'success' not in j or not j['success']:
            raise ValueError("Login failed, please check your student ID and password.")
        if 'token' not in j:
            raise ValueError("Login failed, token not found in response.")
        token = j["token"]
        data = {
            "rand": random.random(),
            "token": token
        }
        req5 = self.session.get("https://portal.pku.edu.cn/portal2017/ssoLogin.do", 
                                params=data, allow_redirects=True, verify=self.verify)
    
    # 获取课表

    def get_schedule(self) -> dict[int, dict[int, str]]:
        '''
        获取课表
        :return: 一个字典,get_schedule()[i][j]表示周i第j节的课程,i=1,2,...,7,j=1,2,...,12.
        课程名包含详细信息，<br>转成换行符
        '''
        req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=coursetable",
                                allow_redirects=True, verify=self.verify)
        if req1.status_code != 200:
            self.login()
            req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=coursetable",
                                   allow_redirects=True, verify=self.verify)
        req2 = self.session.get("https://portal.pku.edu.cn/publicQuery/ctrl/topic/myCourseTable/getCourseInfo.do?xndxq=24-25-2",
                                allow_redirects=True, verify=self.verify)
        if req2.history:  # 被重定向了，说明登录过期
            self.login()
            return self.get_schedule()

        j = req2.json()
        if 'success' not in j or not j['success']:
            raise ValueError("Failed to fetch schedule, please check your login status.")
        if 'course' not in j:
            raise ValueError("Failed to fetch schedule, course data not found in response.")
        course = j['course']
        schedule = {}
        days = ['mon', 'tue', 'wed', 'thu', 'fri', 'sat', 'sun']
        for i in range(1, 8):
            schedule[i] = {}
            for j_index in range(12):
                raw_html = course[j_index][days[i - 1]]['courseName']
                # 用BeautifulSoup把<br>转换成换行
                course_text = BeautifulSoup(raw_html, 'html.parser').get_text(separator='\n').strip()
                schedule[i][j_index + 1] = course_text
        return schedule


    def get_GPA(self) -> str:
        '''
        获取GPA
        :return: GPA值
        '''
        req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=myscores",
                                allow_redirects=True, verify=self.verify)
        if req1.status_code != 200:
            self.login()
            req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=myscores",
                                allow_redirects=True, verify=self.verify)
        req2 = self.session.get("https://portal.pku.edu.cn/publicQuery/ctrl/topic/myScore/retrScores.do",
                                allow_redirects=True, verify=self.verify)
        
        j = req2.json()
        if 'success' not in j or not j['success']:
            raise ValueError("Failed to fetch GPA, please check your login status.")
        if 'gpa' not in j or 'gpa' not in j['gpa']:
            raise ValueError("Failed to fetch GPA, GPA data not found in response.")
        
        gpa = j['gpa']['gpa']
        return gpa
    
    def deepseek(self, text: str, system_text: Optional[str] = None, del_conversation: bool = True) -> str:
        '''
        使用门户的 DeepSeek 功能
        :param text: 要向 DeepSeek 提问的文本
        :param system_text: 系统提示文本，若是None，则使用默认文本
        :param del_conversation: 是否在使用后删除对话，默认为 True
        :return: DeepSeek 的回答
        '''
        if system_text is None:
            system_text = '你是北京大学 AI 助手，专注于为用户提供教育和学习相关的支持。\n- 仅回答学习、科学、文化、技术等正面向上的问题。\n- 不回答涉及政治、法律争议、宗教、黄赌毒、暴力、恐怖组织或恐怖活动等敏感或不适宜讨论的话题。\n- 遵循中国法律法规，立场与中国政府保持一致，提供符合主流价值观的内容。\n- 请确保回答内容积极、客观、准确，并符合青少年及公众可接受的范围。'
        req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=deepseek",
                                 allow_redirects=True, verify=self.verify)
        if req1.status_code != 200:
            self.login()
            req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=deepseek",
                                 allow_redirects=True, verify=self.verify)
        req2 = self.session.get("https://deepseek.pku.edu.cn/api/trpc/chat.getUserAccessibleKnowledgeBases?batch=1&input=%7B%220%22%3A%7B%22json%22%3Anull%2C%22meta%22%3A%7B%22values%22%3A%5B%22undefined%22%5D%7D%7D%7D",
                                 allow_redirects=True, verify=self.verify)
        req3 = self.session.get("https://deepseek.pku.edu.cn/api/trpc/chat.getUserConversationsInKnowledgeBase?batch=1&input=%7B%220%22%3A%7B%22json%22%3A%7B%22knowledgeBaseId%22%3A17%2C%22limit%22%3A50%2C%22offset%22%3A0%7D%7D%7D",
                                 allow_redirects=True, verify=self.verify)
        d = {'0': {'json': {'conversationName': '爬虫专用对话',
                            'knowledgeBaseId': 17,
                            'llm_id': 'deepseek-v3'}}}
        req4 = self.session.post("https://deepseek.pku.edu.cn/api/trpc/chat.createConversation?batch=1",
                                 json=d, allow_redirects=True, verify=self.verify)
        j = req4.json()
        try:
            conID = j[0]['result']['data']['json']['conversationId']
            token = j[0]['result']['data']['json']['token']
        except KeyError:
            raise ValueError("Failed to create conversation, please check your login status.")
        d = {'conversation_id': conID,
             'api_key': token,
             'messages': [{'role': 'system',
                           'content': system_text},
                          {'role': 'user', 'content': text}],
             'model': 'deepseek-v3'}
        req5 = self.session.post("https://deepseek.pku.edu.cn/api/sendQuery",
                                 json=d, allow_redirects=True, verify=self.verify)
        req5.raise_for_status()
        req5.encoding = 'utf-8'
        t = req5.text
        answer_jsons = []
        for i in t.split('\n'):
            if (j := i.strip()):
                try:
                    answer_jsons.append(json.loads(j[6:]))
                except Exception as e:
                    pass
        answer = ''.join(i['choices'][0]['delta']['content'] for i in answer_jsons)
        if del_conversation:
            self.session.post("https://deepseek.pku.edu.cn/api/trpc/chat.deleteConversation?batch=1",
                              json={"0": {"json": {"conversationId": conID}}}, allow_redirects=True, verify=self.verify)
        return answer

if __name__ == "__main__":
    import sys
    import json

    if len(sys.argv) < 4:
        print(json.dumps({"error": "Insufficient arguments"}))
        sys.exit(1)

    function = sys.argv[1]
    stu_id = sys.argv[2]
    password = sys.argv[3]
    verify = sys.argv[4].lower() != "false" if len(sys.argv) > 4 else True

    try:
        if function == "get_schedule":
            portal = Portal(stu_id, password, verify=verify)
            schedule = portal.get_schedule()
            sys.stdout.reconfigure(encoding='utf-8')
            print(json.dumps(schedule, ensure_ascii=False))

        elif function == "get_gpa":
            portal = Portal(stu_id, password, verify=verify)
            gpa = portal.get_GPA()
            print(json.dumps({"gpa": gpa}, ensure_ascii=False))

        elif function == "get_courses":
            course = Course(stu_id, password, verify=verify)
            courses = course.get_all_classes()
            print(json.dumps(courses, ensure_ascii=False))

        else:
            print(json.dumps({"error": "Unknown function"}))

    except Exception as e:
        print(json.dumps({"error": str(e)}))
        sys.exit(1)

