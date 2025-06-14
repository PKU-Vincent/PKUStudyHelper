# -*- coding: utf-8 -*-
'''
使用示例：
c = Course('学号', '密码', verify=False(若需要))
c.get_all_classes()  # 获取所有课程名和链接
p = Portal('学号', '密码', verify=False(若需要))
c.get_schedule()  # 获取课表，门户的返回格式有些奇怪，需要进一步处理
c.get_GPA()  # 获取GPA
c.deepseek('问题')  # 使用门户的 DeepSeek 功能
'''
import requests
import random
from urllib3.exceptions import InsecureRequestWarning
from urllib.parse import quote
import json
from bs4 import BeautifulSoup

# 禁用所有 InsecureRequestWarning 警告
requests.packages.urllib3.disable_warnings(category=InsecureRequestWarning)

class Course:
    '''
    课程信息获取类。提供登录教学网、获取教学网上课程名等功能
    待开发：获取课程作业、公告、文件等功能；获取教学网上的日程表；获取个人成绩；......
    '''

    headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36",
    "Accept-Encoding": "gzip, deflate, br, zstd",
    "Accept-Language": "zh-CN,zh;q=0.9",
    "Connection": "keep-alive"
    }
    def __init__(self, stu_id, password, verify=True):
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
        

class Portal:
    '''
    门户类。提供登录门户、获取课表、GPA、使用门户deepseek等功能
    '''
    def __init__(self, stu_id, password, verify = True):
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
        submit_url = "https://iaaa.pku.edu.cn/iaaa/oauth.jsp?" + "&".join([
            f"appID=portal2017",
            f"appName={quote('北京大学校内信息门户新版')}",
            f"redirectUrl={quote('https://portal.pku.edu.cn/portal2017/ssoLogin.do')}"
        ])
        req3 = self.session.get(submit_url, allow_redirects=True, verify=self.verify)
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
    def get_schedule(self) -> dict:
        '''
        获取课表
        :return: 一个字典，包含课程信息
        '''
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
        return course

    def get_GPA(self) -> str:
        '''
        获取GPA
        :return: GPA值
        '''
        req1 = self.session.get("https://portal.pku.edu.cn/portal2017/util/portletRedir.do?portletId=myscores",
                                allow_redirects=True, verify=self.verify)

        req2 = self.session.get("https://portal.pku.edu.cn/publicQuery/ctrl/topic/myScore/retrScores.do",
                                allow_redirects=True, verify=self.verify)
        if req2.history:
            self.login()
            return self.get_GPA()
        
        j = req2.json()
        if 'success' not in j or not j['success']:
            raise ValueError("Failed to fetch GPA, please check your login status.")
        if 'gpa' not in j or 'gpa' not in j['gpa']:
            raise ValueError("Failed to fetch GPA, GPA data not found in response.")
        
        gpa = j['gpa']['gpa']
        return gpa
    
    def deepseek(self, text: str, del_conversation: bool = True) -> str:
        '''
        使用门户的 DeepSeek 功能
        :param text: 要向 DeepSeek 提问的文本
        :param del_conversation: 是否在使用后删除对话，默认为 True
        :return: DeepSeek 的回答
        '''
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
                           'content': '你是北京大学 AI 助手，专注于为用户提供教育和学习相关的支持。\n- 仅回答学习、科学、文化、技术等正面向上的问题。\n- 不回答涉及政治、法律争议、宗教、黄赌毒、暴力、恐怖组织或恐怖活动等敏感或不适宜讨论的话题。\n- 遵循中国法律法规，立场与中国政府保持一致，提供符合主流价值观的内容。\n- 请确保回答内容积极、客观、准确，并符合青少年及公众可接受的范围。'},
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


