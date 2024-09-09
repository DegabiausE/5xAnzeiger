# This is a sample Python script.

# Press Umschalt+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import requests
import json
import time
import os
import sys
import platform
import locale

from requests import get

def getRequest(Adresse: str):
    result = requests.get(Adresse).text
    result = result.replace('\n','')
    return result

def getRequestHA(Adresse: str):
    headers = {
        "Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI4NzA1MDg3NGM5ZTU0Y2JkOWNkNDUwOTJhMGEwYTVlMiIsImlhdCI6MTcxMjA3MjczNiwiZXhwIjoyMDI3NDMyNzM2fQ.VTVIxJQ4XPw6rNIsH0Uh0B84Aos8oDTTSW7RnySFiwI",
        "content-type": "application/json",
    }
    result = requests.get(Adresse, headers=headers)
    json_opject = json.loads(result.text)
    resultReq = json_opject["state"]

    if is_float(resultReq) == True:
        float_value = locale.atof(resultReq)
        if abs(float_value) < 99 and not float_value == 0:
            returnString = str("%.1f" % float_value)
        else:
            returnString = str("%.0f" % float_value)
        return returnString
    else:
        if "available" in resultReq.lower():
            return "NA"
        else:
            return resultReq

def is_float(string):
    try:
        float(string)
        return True
    except ValueError:
        return False

print("Start")

SourceFileName = ['Display1.json','Display2.json','Display3.json','Display4.json','Display5.json','Display6.json','Display7.json','Display8.json','Display9.json','Display10.json']
TargetFileName = ['result1.json', 'result2.json', 'result3.json', 'result4.json', 'result5.json', 'result6.json', 'result7.json', 'result8.json', 'result9.json', 'result10.json']
if platform.system() == "Windows":
    print('Hello world', file=sys.stderr)
    TargetLink = "//192.168.1.20//Data//Tools//Web//"
elif platform.system() == "Linux":
    print('Hello world Linux', file=sys.stderr)
    TargetLink = "//web//"

while True:
    #json laden
    try:
        for FileNr in range(len(SourceFileName)):

            f = open(SourceFileName[FileNr])
            data = json.load(f)


            for z in range(0, len(data['elements'])):
                if "value" in data['elements'][z]:
                    value = data['elements'][z]['value']
                    Typ = data['elements'][z]['type']
                    if value.find('{') > -1 and value.find('}') > -1 and Typ == "Text":
                        PosStart = value.find('{')
                        PosEnd = value.rfind('}')
                        HttpLink = value[PosStart+1 : PosEnd]
                        if HttpLink.find('192.168.1.20:8123')>0:
                            Request = getRequestHA(HttpLink)
                        if HttpLink.find('192.168.1.20:8083')>0:
                            Request = getRequest(HttpLink)

                        data['elements'][z]['value'] = value.replace(value[PosStart : PosEnd+1], Request)
                    if value.find('{') > -1 and value.find('}') > -1 and Typ == "Bild":
                        PosStart = value.find('{')
                        PosEnd = value.rfind('}')
                        HttpLink = value[PosStart+1 : PosEnd]
                        if HttpLink.find('192.168.1.20:8123')>0:
                            Request = getRequestHA(HttpLink)
                        if HttpLink.find('192.168.1.20:8083') > 0:
                            Request = getRequest(HttpLink)
                        data['elements'][z]['value'] = value.replace(value[PosStart : PosEnd+1], Request)

            with open(TargetLink + TargetFileName[FileNr], 'w') as fp:
                json.dump(data, fp, indent=4)
                time.sleep(1)
    except:
        print('Ausnahme', file=sys.stderr)