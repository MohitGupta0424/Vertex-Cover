import re
import sys

error_message=''
lst = []
class ValidateInput(object):
    def validateInput(self,userInput):
        userInput = userInput.strip()
        if userInput[0] == 'a'or userInput[0] == 'c' or userInput[0] == 'r' or userInput[0] == 'g':
            if userInput[0] == 'a':
                st=""
                count1 = count2 = count3 =0
                if userInput[1:].strip()[0] == "\"":
                    pass
                else:
                    self.setErrorMessage('Error: Invalid Input char found between the cmd and StreetName') 
                    return False   
                if len(userInput.split('\"')) == 3:
                    if userInput.split('\"')[1] =="" or userInput.split('\"')[1] == " ":
                        self.setErrorMessage('Error: Invalid Street Name Given') 
                        return False    
                else:
                    self.setErrorMessage('Error: Invalid Street Name Given') 
                    return False
                for i in range(len(userInput)):
                    if userInput[i] == "\"":
                        j = i 
                for k in range(j,len(userInput)):
                    if userInput[k] == "(":
                        st = userInput[j+1:k]
                        break        
                for i in range(len(st)):
                    if st[i]==" " or st[i]=="":
                        pass
                    else:
                        self.setErrorMessage('Error: Invalid Input str found between StreetName and coordinates') 
                        return False
                for i in range(len(userInput)):
                    if userInput[i] == "(":
                        count1+=1
                    elif userInput[i] == ")":
                        count2+=1    
                    elif userInput[i] == ",":
                        count3+=1
                if count1 == count2 == count3:
                    pass
                else:
                    self.setErrorMessage('Error: Invalid Input brackets and commas does not match')
                    return False
                if count1>=2:
                    pass
                else:
                    self.setErrorMessage('Error: Invalid Input.Provide atleast 2 points')
                    return False
        else:
            error_message ='Error: Input should start with a,c,r,g' 
            self.setErrorMessage(error_message) 
            return False

        if userInput[0] == 'a' or userInput[0] == 'c' or userInput[0] == 'r':
            if userInput[1] == " ":
                pass
            else:
                self.setErrorMessage('Error: The second character should be a space.') 
                return False
        if userInput[0] == 'a' or userInput[0] == 'c':
            for m in range(len(userInput)):
                if userInput[m] == '(':
                    if userInput[m-1] == " ":
                        break
                    else:
                        self.setErrorMessage('Error:  space needed after street name.')
                        return False   
            a = userInput.find('(')
            userInputlst = userInput.split("(")
            for i in range(len(userInputlst)-1):
                if "," in userInputlst[i]:
                    for j in range(i+1,len(userInputlst)):
                        point1 = userInputlst[i].strip()[:-1].strip().split(',')
                        x1 = point1[0]
                        y1 = point1[1]
                        point2 = userInputlst[j].strip()[:-1].strip().split(',')
                        x2 = point2[0]
                        y2 = point2[1]
                        if x1 == x2 and y1==y2:
                            self.setErrorMessage('Error:  Points in same street cannot be same.')
                            return False
            input = userInput[a+1:len(userInput)-1]
            regex = re.compile('[a-z]|[A-Z]')
            if len(regex.findall(input))>0:
                self.setErrorMessage('Error: String found in the characters.')
                return False
            else:
                pass

    def removeSpaceCoordinates(self,userInput):
        s=""
        j=0
        i=0
        regex = re.compile('[a-z]|[A-Z]')
        while i < (len(userInput)):
            if userInput[i] == "(":
                j=i
                while userInput[j] !=")":
                    if userInput[j] == " ":
                        i+=1
                        j+=1
                    else:
                        if len(regex.findall(userInput[j]))>0:
                            self.setErrorMessage("Error: Coordinates cannot be [a-z][A-Z]")
                            return False
                        else:
                            s = s+userInput[j]  
                            j+=1
                            i+=1
                s = s+userInput[j]
                if j != len(userInput)-1:
                    if userInput[j+1] != " ":
                        s = s + " "        
            else:
                s=s+userInput[i] 
            i+=1       
        return s                     


    def setErrorMessage(self,message):
        pass
        #sys.stderr.write(message)

    def validateAddCase(self, streetName, streetDict):
        street = streetDict.keys()
        flag = False
        for i in range(len(street)):
            if streetName.lower() == street[i].lower():
                flag = True
            else:
                flag = False
                break    
        if flag == True:        
            self.setErrorMessage("Error: The street already exists")
            return False
        else:
            return True

    def validateChangeCase(self, streetName, streetDict,userInput):
        street = streetDict.keys()
        count=0
        flag = False
        for i in range(len(userInput)):
            if userInput[i] == "(":
                count+=1
        for j in range(len(street)):        
            if streetName.lower() != street[j].lower() or count <2:
                flag = True
            else:
                flag = False
                break    
        if flag == True:
            self.setErrorMessage("Error: The street does not exist or coordinates should be more than 2.")
            return False
        else:    
            return True 

    def validateRemoveCase(self, streetName, streetDict,userInput):
        street = streetDict.keys()
        flag = False
        elements = userInput.strip().split("\"")
        for i in range(len(street)):
            if streetName.lower() != street[i].lower() or elements[-1] != '':
                flag = True
            else:
                flag = False
                break    
        if flag == True:        
            self.setErrorMessage("Error: The street does not exist or invalid input")
            return False
        return True 

    def validateGenerateCase(self, streetDict,userInput):
        street = streetDict.keys()
        if len(userInput.strip()) == 1:
            return True
        else:
            self.setErrorMessage("Error: Invalid Input ")
            return False