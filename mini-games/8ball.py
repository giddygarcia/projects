# Made by Christine Garcia
# After self-learning Python and Tkinter basics

import random
from tkinter import *

window = Tk()
window.minsize(300, 50)
window.title("8ball of words")

# excerpts of answers taken from: https://magic-8ball.com/magic-8-ball-answers/
Eightball_list = [ "It is certain", "It is decidedly so", "Without a doubt", "Yes", "Most likely",
					"No", "Don't count on it", "My sources say no", "Very doubtful", "My reply is no",
					"Reply hazy, try again", "Ask again later", "Better not tell you now" ]

answer = Label(window)
def printAnswer(event):
	answer.configure(text=(random.choice(Eightball_list)))	
answer.pack()

label = Label(window, text="What is your question?")
label.pack()

question = Entry(window)
question.pack()

button = Button(window, text="Ask")
button.bind('<Button-1>', printAnswer)
window.bind('<Return>', printAnswer)
button.pack()

window.mainloop()