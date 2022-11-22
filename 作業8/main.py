import tkinter
import tkinter.messagebox
from tkinter import ttk
from tkinter import filedialog as fd
from tkinter.constants import *

if __name__ == '__main__':
    print("main.py is ready")

    # create a new window
    window = tkinter.Tk()
    window.title("Homework 7")

    # create two picture
    img = tkinter.Label(window,relief = 'solid', width = 80, height = 30)

    # size control
    window.geometry('800x500')

    # title
    lbl_title = tkinter.Label(window, text = "Homework 8", font=("Arial",18))

    # open file
    btn_open = tkinter.Button(window, text = 'Open', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    # save file
    btn_save = tkinter.Button(window, text = 'Save', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    # reset photo
    btn_reset = tkinter.Button(window, text = 'Reset', bg = 'light cyan', font = ('Arial', 18), width = 7, height = 1)

    #place
    img.place(x = 175, y = 20)
    lbl_title.place(x=10, y=0)
    btn_open.place(x = 20, y = 50)
    btn_save.place(x = 20, y = 125)
    btn_reset.place(x = 20, y = 200)

    window.mainloop()