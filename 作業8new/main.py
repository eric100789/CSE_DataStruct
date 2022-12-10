import tkinter
import tkinter.messagebox
from tkinter import ttk
from tkinter import filedialog as fd
from tkinter.constants import *
import os

def encodeFile(encodeFile):
    global window,label
    if encodeFile == "":
        msg = "你不能在甚麼都沒有輸入的情況下渴望Encode"
        tkinter.messagebox.showerror(title = '請輸入檔名', message = msg)
        return False
    fileName = fd.askopenfilename()
    if not fileName:
        return False
    f=""
    for i in range(len(fileName)-1,-1,-1):
        if fileName[i] == '/':
            break
        f = fileName[i]+f

    cpptest="huffman.exe"
    if os.path.exists(cpptest):
        f=os.popen("%s %s %s %s %s"%(cpptest,"ENCODE",f,encodeFile,"OK"))
        data=f.readlines()
        f.close()
    print(data)
    text = ""
    for i in range(len(data)):
        if(i%2 == 0):
            text += data[i][0:-1]
        else:
            text += ":" + data[i][0:-1] + "   "
        if((i+1)%12 == 0 and i!=0):
            text += '\n'
    label.config(text=text, justify="left",relief = 'solid', width = 100, height = 40)

def decodeFile(decodeFile):
    global window,label
    if decodeFile == "":
        msg = "你不能在甚麼都沒有輸入的情況下渴望Decode"
        tkinter.messagebox.showerror(title = '請輸入檔名', message = msg)
        return False
    fileName = fd.askopenfilename()
    if not fileName:
        return False
    f=""
    for i in range(len(fileName)-1,-1,-1):
        if fileName[i] == '/':
            break
        f = fileName[i]+f

    cpptest="huffman.exe"
    if os.path.exists(cpptest):
        f=os.popen("%s %s %s %s %s %s"%(cpptest,"ENCODE",f,decodeFile,"OK","LOTOFOK"))
        f.close()
    label.config(text="File decode successfully!", justify="left",relief = 'solid', width = 100, height = 40)


if __name__ == '__main__':
    print("main.py is ready")

    # create a new window
    window = tkinter.Tk()
    window.title("Homework 7")

    # create two picture
    label = tkinter.Label(window,relief = 'solid', width = 100, height = 40)

    # size control
    window.geometry('950x700')

    # title
    lbl_title = tkinter.Label(window, text = "Homework 8", font=("Arial",18))

    # encode file
    btn_encode = tkinter.Button(window, text = 'Encode', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1, command= lambda: encodeFile(ent_encode.get()))
    lbl_encode = tkinter.Label(window, text = "Input your encoded file's name:", font=("Arial",9))
    ent_encode = tkinter.Entry(window,width=20)

    # save file
    btn_decode = tkinter.Button(window, text = 'Decode', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1, command= lambda: decodeFile(ent_decode.get()))
    lbl_decode = tkinter.Label(window, text = "Input your decoded file's name:", font=("Arial",9))
    ent_decode = tkinter.Entry(window,width=20)

    # reset photo
    btn_reset = tkinter.Button(window, text = 'Reset', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    #place
    label.place(x = 200, y = 20)
    lbl_title.place(x=10, y=0)

    #Encode place
    btn_encode.place(x = 20, y = 50)
    lbl_encode.place(x = 20, y = 100)
    ent_encode.place(x = 20, y = 125)

    #Decode place
    btn_decode.place(x = 20, y = 175)
    lbl_decode.place(x = 20, y = 225)
    ent_decode.place(x = 20, y = 250)

    window.mainloop()