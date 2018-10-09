import urllib.request
from bs4 import BeautifulSoup
import re
head = {}
head['User-Agent'] = 'Mozilla/5.0 (Linux; Android 4.1.1; Nexus 7 Build/JRO03D) AppleWebKit/535.19 (KHTML, like Gecko) Chrome/18.0.1025.166  Safari/535.19'
f = open("./result.txt",'w', encoding='utf-8')
target_req = urllib.request.Request(url = 'http://openaccess.thecvf.com/CVPR2018.py', headers = head)
file=urllib.request.urlopen(target_req)
#file=urllib.request.urlopen('http://openaccess.thecvf.com/CVPR2018.py')
data = file.read()
soup = BeautifulSoup(data,'html.parser')

# text = soup.body.dl.find_all('dt').find_all['href']
cnt=-1
dts = soup.find_all('dt', class_='ptitle')
for dt in dts:
    tag = dt.find('a')
    url = 'http://openaccess.thecvf.com/' + tag['href']
    cnt+=1
    f.write(str(cnt)+'\n')
    # f.write(url+'\n\n')
    file = urllib.request.urlopen(url)
    data = file.read()
    #soup = BeautifulSoup(data, 'html.parser')
    #dts2 = soup.find(id = 'papertitle' + id = 'abstract')
    soup = BeautifulSoup(data, 'html.parser')
    dts2 = soup.find(id = 'papertitle')
    soup = BeautifulSoup(data, 'html.parser')
    dts3 = soup.find(id = 'abstract')
    soup = BeautifulSoup(data, 'html.parser')
    dts4 = soup.find('i')
    soup = BeautifulSoup(data, 'html.parser')
    tag2 = soup.find('div', id = 'content').find('a')
    url2 = tag2['href'].replace('../..', 'http://openaccess.thecvf.com')
    #url = soup.body.div.dl.dd.a['href']
    #url = dts5['href']
    print(cnt)
    #print(url)
    #print(dts2.string)
    #print(dts3.string)
    #dts2 = dts2.string.replace(contents[0], 'Title: ')
    #dts2 = dts2.string.replace(contents[2], 'Abstract: ')
    title = dts2.string.replace('\n', 'Title: ')
    #title = title.encode("GB18030")
    #title = title.replace('\xe2', 'ignore')
    #title = title.replace('\u2212', 'ignore')
    #title = title.replace('\u223c', 'ignore')
    #auther = dts4.string.replace('\n', 'Auther: ')

    abstract = dts3.string.replace('\n', 'Abstract: ')
    #abstract = abstract.encode("GB18030")
    #abstract = abstract.replace('\xe2', 'ignore')
    #abstract = abstract.replace('\u2212', 'ignore')
    #abstract = abstract.replace('\u223c', 'ignore')
    #f.write(dts2)
    
    f.write(title+'\n'+'Authors: '+dts4.string+'\n'+abstract+'\n'+'PDF URL: '+url2+'\n\n\n')
    #f.write('Authors: '+dts4.string+'\n')
    #f.write(abstract+'\n\n\n')
f.close()

# text1 = text.dl.find_all('dt')
# print(text)
'''for child in text1.children:
     print(a)'''
'''
for tag in text1.find_all('href'):
    print(tag.name)'''
#text1 = text.dl.dt.a['href']

#text2 = text.find_all(class_='authsearch')
#print(tag)
#print(text2)
#print(text)
#texts = BeautifulSoup(str(text),'html.parser')
# print(soup.find_all('a'))
#print(soup.div.id['content'])
'''fhandle=open("./result.html","wb")
fhandle.write(text)
fhandle.close()
f = open('result.txt', 'w', encoding='utf-8')

f = open("./result.txt",'wb')
f.write(text)
f.close()
'''