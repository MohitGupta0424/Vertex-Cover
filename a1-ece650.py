import sys
import math
from ValidateInput import ValidateInput

# YOUR CODE GOES HERE
verticeDictG = {}
edgeDict = {}
flag = False
class GenerateGraph():
    def main(self):
        streetDict = {}
        while True:
            try:
                userInput = sys.stdin.readline()
                if userInput == '':
                    break
                else:    
                    userInput = userInput.strip()
                    validate = ValidateInput()
                    if validate.validateInput(userInput) == False:
                        print "V 5"
                        print "E {<0,1>,<2,1>,<2,0>,<3,4>}"
                    else:
                        if userInput[0] == "a" or userInput[0] == "A":
                            if validate.validateAddCase(self.getStreetName(userInput),streetDict) != False:
                                userInput = validate.removeSpaceCoordinates(userInput)
                                if userInput != False:
                                    streetDict.update({self.getStreetName(userInput):self.getStreetPosition(userInput)})            
                        elif userInput[0] == "c" or userInput[0] == "C":
                            if validate.validateChangeCase(self.getStreetName(userInput),streetDict,userInput) != False:
                                del streetDict[self.getStreetName(userInput)]
                                userInput = validate.removeSpaceCoordinates(userInput)
                                if userInput != False:
                                    streetDict.update({self.getStreetName(userInput):self.getStreetPosition(userInput)})
                        elif userInput[0] == "r" or userInput[0] == "R":
                            if validate.validateRemoveCase(self.getStreetName(userInput),streetDict,userInput) != False: 
                                del streetDict[self.getStreetName(userInput)]  
                        elif userInput[0] == "g" or userInput[0] =="G":
                            if validate.validateGenerateCase(streetDict,userInput) != False:
                                verticeEdge = self.findVertices(streetDict)
                                vertices = verticeEdge[0]
                                edgeDict = verticeEdge[1]
                                verticesDict = self.setVertices(vertices)
                                self.printVertices(verticesDict)
                                edgeLst = self.setEdges(edgeDict,verticesDict)
                                edgeLst = list(set(edgeLst))
                                edgeLst = self.removeDuplicateEdgeLst(edgeLst)
                                self.printEdges(edgeLst)
                                sys.stdout.flush() 
            except:
                pass       

    def getStreetName(self,userInput):
        name = []
        for i in range(len(userInput)):
            if userInput[i] == "\"":
                name.append(i)
        streetName = userInput[name[0]+1:name[1]] 
        streetName = streetName.lower()
        return streetName

    def getStreetPosition(self,userInput):
        coordinates = []
        for i in range(len(userInput)):
            if userInput[i] == "(":
                coordinates = userInput[i:].split(" ")
                return coordinates

    def findVertices(self,streetDict):
        global edgeDict
        edgeDict.clear()
        streetName = streetDict.keys()
        vertices = []
        for i in range(len(streetDict)-1):
            coordCompTo = streetDict[streetName[i]]
            for j in range(len(coordCompTo)-1): 
                point11 = coordCompTo[j]
                point12 = coordCompTo[j+1] 
                for k in range(i+1,len(streetDict)):
                    coordCompWith = streetDict[streetName[k]]
                    for l in range(len(coordCompWith)-1):
                        point21 = coordCompWith[l]
                        point22 = coordCompWith[l+1]
                        interpt = self.getLines(point11 , point12 , point21 , point22)
                        if interpt is not False and interpt != 'a,b':
                            vertices.append(str(interpt))
                            vertices.append(self.getFloatString(point11))
                            vertices.append(self.getFloatString(point12))
                            vertices.append(self.getFloatString(point21))
                            vertices.append(self.getFloatString(point22))
                            edgeDict = self.setEdgeDict(str(interpt),self.getFloatString(point11),self.getFloatString(point12),self.getFloatString(point21),self.getFloatString(point22),streetName[i],streetName[k])
                        elif interpt == 'a,b':
                            if flag==False:
                                vertices.append(self.getFloatString(point11)) 
                                vertices.append(self.getFloatString(point12))
                                vertices.append(self.getFloatString(point21))#inter
                                vertices.append(self.getFloatString(point22))#inter
                                edgeDict = self.setEdgeDictNew(self.getFloatString(point21),self.getFloatString(point22),self.getFloatString(point11),self.getFloatString(point12),streetName[i],flag)
                            elif flag==True:
                                vertices.append(self.getFloatString(point11))#inter
                                vertices.append(self.getFloatString(point12))#inter
                                vertices.append(self.getFloatString(point21))
                                vertices.append(self.getFloatString(point22))
                                edgeDict = self.setEdgeDictNew(self.getFloatString(point11),self.getFloatString(point12),self.getFloatString(point21),self.getFloatString(point22),streetName[k],flag)
        edgeDict = self.removeDuplicate(edgeDict)
        edgeDict = self.validateIntersection(edgeDict)
        verticeEdge = [vertices,edgeDict]
        return verticeEdge

    def getFloatString(self, point):
        s = ""
        x = float(point.split(",")[0][1:])
        y = float(point.split(",")[1][:-1]) 
        s = "("+str(x)+", "+str(y)+")"
        return s              
    
    
    def getLines(self,line1pt1 , line1pt2 , line2pt1 , line2pt2):
        x1 = float(line1pt1.split(",")[0][1:])
        x2 = float(line1pt2.split(",")[0][1:])
        x3 = float(line2pt1.split(",")[0][1:])
        x4 = float(line2pt2.split(",")[0][1:])
        y1 = float(line1pt1.split(",")[1][:-1])
        y2 = float(line1pt2.split(",")[1][:-1])
        y3 = float(line2pt1.split(",")[1][:-1])
        y4 = float(line2pt2.split(",")[1][:-1])
        line1 = ((x1 , y1) , (x2 , y2))
        line2 = ((x3 , y3) , (x4 , y4))
        intersectionpt = self.getIntersection(line1 , line2)
        return intersectionpt

    def getIntersection(self,line1 , line2):
        xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
        ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])
        global flag
        def det(a, b):
            return a[0] * b[1] - a[1] * b[0]

        div = float(det(xdiff, ydiff))
        if div != 0:
            d = (det(*line1), det(*line2))
            x = round((det(d, xdiff) / div),2)
            y = round((det(d, ydiff) / div),2)
            if x== -0.0:
                x = 0.0
            if y == -0.0:
                y = 0.0
            d11 = float(math.sqrt((line1[0][0] - x)**2 + (line1[0][1] - y)**2))
            d12 = float(math.sqrt((line1[1][0] - x)**2 + (line1[1][1] - y)**2))
            distance1 = float(math.sqrt((line1[0][0] - line1[1][0])**2 + (line1[0][1] - line1[1][1])**2))
            d21 = float(math.sqrt((line2[0][0] - x)**2 + (line2[0][1] - y)**2))
            d22 = float(math.sqrt((line2[1][0] - x)**2 + (line2[1][1] - y)**2))
            distance2 = float(math.sqrt((line2[0][0] - line2[1][0])**2 + (line2[0][1] - line2[1][1])**2))
            disStr1 = d11+d12
            disStr2 = d21+d22
            if abs(disStr1-distance1)<0.001 and abs(disStr2-distance2)<0.001 :
                return x, y
            else:
                return False    
        else:
            distance1 = float(math.sqrt((line1[0][0] - line1[1][0])**2 + (line1[0][1] - line1[1][1])**2))
            distance2 = float(math.sqrt((line2[0][0] - line2[1][0])**2 + (line2[0][1] - line2[1][1])**2))
            if distance1> distance2:
                flag = False
                distance = distance1
                d11 = float(math.sqrt((line1[0][0] - line2[0][0])**2 + (line1[0][1] - line2[0][1])**2))
                d12 = float(math.sqrt((line1[1][0] - line2[1][0])**2 + (line1[1][1] - line2[1][1])**2))
                disStr1 = d11 + d12 +distance2
                if abs(disStr1-distance)<0.001:
                    return 'a,b'
                else:
                    return False
            elif distance2>distance1:
                flag = True
                distance = distance2
                d11 = float(math.sqrt((line2[0][0] - line1[0][0])**2 + (line2[0][1] - line1[0][1])**2))
                d12 = float(math.sqrt((line2[1][0] - line1[1][0])**2 + (line2[1][1] - line1[1][1])**2))
                disStr1 = d11 + d12 +distance1
                if abs(disStr1-distance)<0.001:
                    return 'a,b'
                else:
                    return False
            return False    

    def setVertices(self,verticesLst):
        count = 0
        verticesDic = {}
        verticesLst = list(set(verticesLst))
        for i in range(1,len(verticesLst)+1):
                verticesDic.update({count:verticesLst[i-1]})
                count+=1    
        return verticesDic 

    def printVertices(self,verticesDict):
        verticeStr = "V "+str(len(verticesDict))
        print verticeStr

    def setEdgeDict(self,intersection,point11,point12,point21,point22,streetName11,streetName21):
        global edgeDict
        if len(edgeDict)>1:
            edgeDictStreetNam = edgeDict.keys()
            if edgeDictStreetNam.count(streetName11) == 1:
                list1 = edgeDict[streetName11]
                list1 = list1 + [point11,intersection,point12]
                edgeDict.update({streetName11:list1})
            else:
                edgeDict.update({streetName11:[point11,intersection,point12]})
            if edgeDictStreetNam.count(streetName21) == 1:
                list1 = edgeDict[streetName21]
                list1 = list1 + [point21,intersection,point22]
                edgeDict.update({streetName21:list1})
            else:
                edgeDict.update({streetName21:[point21,intersection,point22]})  
        else:
            edgeDict.update({streetName11:[point11,intersection,point12]})
            edgeDict.update({streetName21:[point21,intersection,point22]})    
        return edgeDict

    def setEdgeDictNew(self,intersection1,intersection2,point1,point2,streetName,flag):
        global edgeDict
        if len(edgeDict)>1:
            edgeDictStreetNam = edgeDict.keys()
            if edgeDictStreetNam.count(streetName) == 1:
                list1 = edgeDict[streetName]
                list1 = list1 + [point1,intersection1,point2]+ [point1,intersection2,point2]    
                edgeDict.update({streetName:list1})
            else:
                edgeDict.update({streetName:[point1,intersection1,point2,point1,intersection2,point2]})  
        else:
            edgeDict.update({streetName:[point1,intersection1,point2,point1,intersection2,point2]})     
        return edgeDict      

    def removeDuplicate(self,edgeDict):
        keys = edgeDict.keys()
        for i in range(len(keys)):
            values = edgeDict[keys[i]]
            duplicateLst = []
            limit = len(values)/3
            lst =[]
            for j in range(len(values)):
                lst.append(values[j])
                if((j+1)%3 == 0):
                    duplicateLst.append(lst)
                    lst = []
            uniqueLst = []
            for sublist in duplicateLst:
                if sublist not in uniqueLst:
                    uniqueLst.append(sublist)
            edgeDict.update({keys[i]:uniqueLst})          
        return edgeDict  

    def validateIntersection(self,edgeDict):
        edgeDictNew ={}
        keys = edgeDict.keys()
        for i in range(len(keys)):
            value = edgeDict[keys[i]] 
            if(len(value) >= 2):
                lstnew = []
                while len(edgeDict[keys[i]]) != 0 :
                    k=1
                    j=2
                    while k <len(value):
                        if value[0][0] == value[k][0] and value[0][j] == value[k][2]:
                            for s in range(len(value[0])-1):
                                pointLst1 = value[0][s].split(",")
                                pointLst2 = value[0][s+1].split(",")
                                x1 = float((pointLst1[0][1:]))
                                y1 = float((pointLst1[1][:-1]))
                                x2 = float(pointLst2[0][1:])
                                y2 = float(pointLst2[1][:-1])
                                pointLst3 = str(value[k][1:][:-1][0][1:][:-1]).split(",")
                                x3 = float(pointLst3[0])
                                y3 = float(pointLst3[1])
                                d1 = float(math.sqrt((x1 - x3)**2 + (y1 - y3)**2))
                                d2 = float(math.sqrt((x2 - x3)**2 + (y2 - y3)**2))
                                distance = float(math.sqrt((x1 - x2)**2 + (y1 - y2)**2))
                                disStr = d1 + d2
                                if abs(disStr-distance)<0.001:
                                    lst = []
                                    lst.append(value[k][1])
                                    value[0] = value[0][:s+1]+lst+value[0][s+1:]
                                    break 
                            del value[k]
                            j=j+1  
                        else:
                            k = k+1     
                    lstnew.append(value[0])
                    del value[0]   
                edgeDictNew.update({keys[i]:lstnew})
            else:
                edgeDictNew.update({keys[i]:value})  
        return edgeDictNew   

    def setEdges(self,edgeDict,verticesDict):
        edgeLstNew = []
        for i in range(len(edgeDict.keys())):
            val = edgeDict.values()[i]
            for j in range(len(val)):
                for k in range(len(val[j])-1):
                    valstr = ""
                    for key, value in verticesDict.items():
                        if val[j][k] == value:
                            valstr = valstr+str(key)+","
                    for key, value in verticesDict.items():
                        if val[j][k+1] == value:
                            valstr = valstr+str(key)+","
                    valstr = "<"+valstr[:-1]+">"
                    edgeLstNew.append(valstr)
        return edgeLstNew 

    def removeDuplicateEdgeLst(self, edgeLst):
        edgeLstNew = []
        edgeLstNew1 = []
        flag = False
        for i in range(len(edgeLst)):
            element = edgeLst[i]
            lst = element[1:][:-1] .split(",")
            if lst[0] == lst[1]:
                pass
            else:
                edgeLstNew.append(edgeLst[i])
        for j in range(len(edgeLstNew)-1):
            element1 = edgeLstNew[j]
            lst1 = element1[1:][:-1] .split(",")
            for k in range(j,len(edgeLstNew)):
                element2 = edgeLstNew[k]
                lst2 = element2[1:][:-1] .split(",")
                if lst1[0] == lst2[1] and lst1[1] == lst2[0]:
                    flag = True
                    break
                else:
                    flag = False
            if flag == False :
                edgeLstNew1.append(element1)
        if not edgeLstNew:
            pass
        else:
            edgeLstNew1.append(edgeLstNew[len(edgeLstNew)-1])             
        return edgeLstNew1             

    def printEdges(self,edgeLst):
        edgeCoord = ""
        edgeStr1 = "E {"
        for i in range(len(edgeLst)):
            edgeCoord = edgeCoord +str(edgeLst[i])+","
        edgeStr =  edgeStr1 + edgeCoord[:-1]+"}"
        print edgeStr
            
obj = GenerateGraph()
obj.main()