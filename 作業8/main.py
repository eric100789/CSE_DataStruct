import tkinter
import tkinter.messagebox
from tkinter import ttk
from tkinter import filedialog as fd
from tkinter.constants import *
import os

def openfile():
    global window,label
    file_name = fd.askopenfilename()

    cpptest="huffman.exe"
    if os.path.exists(cpptest):
        f=os.popen("%s %s"%(cpptest,file_name))
        data=f.readlines()
        f.close()
    print(data)
    text = "";
    for i in range(len(data)):
        if(i%2 == 0):
            text += data[i][0:-1]
        else:
            text += ":" + data[i][0:-1] + "   "
        if((i+1)%12 == 0 and i!=0):
            text += '\n'
    lbl_data = tkinter.Label(window,text=text, justify="left")
    lbl_data.place(x = 175, y = 20)


if __name__ == '__main__':
    print("main.py is ready")

    # create a new window
    window = tkinter.Tk()
    window.title("Homework 7")

    # create two picture
    label = tkinter.Label(window,relief = 'solid', width = 100, height = 40)

    # size control
    window.geometry('920x700')

    # title
    lbl_title = tkinter.Label(window, text = "Homework 8", font=("Arial",18))

    # open file
    btn_open = tkinter.Button(window, text = 'Open', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1, command=openfile)

    # save file
    btn_save = tkinter.Button(window, text = 'Save', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    # reset photo
    btn_reset = tkinter.Button(window, text = 'Reset', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    #place
    label.place(x = 175, y = 20)
    lbl_title.place(x=10, y=0)
    btn_open.place(x = 20, y = 50)
    btn_save.place(x = 20, y = 125)
    btn_reset.place(x = 20, y = 200)

    window.mainloop()