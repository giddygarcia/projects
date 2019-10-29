#Giddy Garcia 2019
#Made with Python 3 & tkinter after self-teaching both the language and GUI toolkit.

import tkinter as tk
from tkinter.font import Font
import re

root = tk.Tk()
root.minsize(300,150)
root.title("Python Calculator w GUI")

arial12 = Font(family="Arial", size=12, weight="bold")
arial18 = Font(family="Arial", size=18, weight="bold")

equation = ''

display = tk.Text(root, state="disabled", width=20, height=1, background="lightblue", font=arial18)
display.grid(row=0, columnspan=3)

def createNumButtons(val,write=True,width=7):
    return tk.Button(root, text=val, command=lambda:click(val,write), width=width, font=arial12)   

lst_of_buttons=[]
for i in range(10):
    createNumButtons(i)
    lst_of_buttons.append(createNumButtons(i))

count = 1
for row in range(1,4):
    for column in range(3):
        lst_of_buttons[count].grid(row=row,column=column)
        count += 1

zero = createNumButtons(0)
zero.grid(row=4,column=1)
equal = createNumButtons('=', None, 28) 
equal.grid(row=5,column=0, columnspan=3)
clear = createNumButtons(u"\u232B", None) 
clear.grid(row=0,column=4)
plus = createNumButtons('+') 
plus.grid(row=1, column=4)
minus = createNumButtons('-') 
minus.grid(row=2,column=4)
mult = createNumButtons('*') 
mult.grid(row=3,column=4)
div = createNumButtons(u"\u00F7")
div.grid(row=4,column=4)

def update(value, newline=False):
	global equation
	display.configure(state='normal')
	display.insert(tk.END, value)
	equation += str(value)
	display.configure(state='disabled')

def click( text, write):
	global equation
	if write == None:
		if text == '=' and equation:
			equation = re.sub(u"\u00F7", '/', equation)
			answer = str(eval(equation))
			clear()
			update(answer,newline=True)
		elif text == u"\u232B":
			clear()
	else:
		update(text)

def clear():
	global equation
	equation = ''
	display.configure(state='normal')
	display.delete('1.0', tk.END)
	
root.mainloop()