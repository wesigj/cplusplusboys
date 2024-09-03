from urllib import request
from lxml import etree
import xlwt
import ssl
import random
#添加user-agent用户代理
ua_list=['Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.26 Safari/537.36 Core/1.63.6726.400 QQBrowser/10.2.2265.400',
         'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36',
         'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.101 Safari/537.36',
         'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.11 TaoBrowser/2.0 Safari/536.11'
        'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.71 Safari/537.1 LBBROWSER',
         'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.84 Safari/535.11 SE 2.X MetaSr 1.0',
         'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Maxthon/4.4.3.4000 Chrome/30.0.1599.101 Safari/537.36',
         'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.122 UBrowser/4.0.3214.0 Safari/537.36'
         ]
xPathStr='//*/div[@class="article-list"]/div/h4'
# 读取网站
def readURL(url):
    user_agent=random.choice(ua_list)
    headers={'User-Agent':user_agent}
    context=ssl._create_unverified_context()
    html = request.urlopen(request.Request(url,headers=headers),context=context).read().decode('utf8')
    return html
# xpath节点获取并写入表格
def htmlxPath(html,sheet,i):
    htmls = etree.HTML(html)
    result = htmls.xpath(xPathStr)
    for res in result:
        i += 1
        url = res.xpath('a/@href')[0]
        title = res.xpath('a/text()')[1].replace(' ', '')
        sheet.write(i, 0, title)
        sheet.write(i, 1, url)
    return i
 
def articleSpider(url,beginPage,endPage):
    workbook = xlwt.Workbook()
    sheet = workbook.add_sheet('csdn博主文章')
    sheet.write(0, 0, '标题')
    sheet.write(0, 1, '文章地址')
    i=0
    for page in range(beginPage,endPage+1):
        # 拼接地址，?t=1表示栓选原创文章
        fullurl=f'{url}{page}?t=1'
        html=readURL(fullurl)
        i=htmlxPath(html,sheet,i)
    workbook.save('csdn.xls')
 
if __name__=='__main__':
    bloggerId=input('请输入要爬取的博主Id:')
    beginPage=int(input('请输入开始的页数：'))
    endPage=int(input('请输入结束的页数：'))
    url=f'https://blog.csdn.net/{bloggerId}/article/list/'
    articleSpider(url,beginPage,endPage)
 