from tkinter import *
import json
import requests

def right_click(event):
	try:
		response = requests.get('http://localhost:3000/raw').content 
		j = json.loads(response)
		jWeather.configure(text=str(j["description"]))
		jText.configure(text=str(j["temp"]) + "°C")
	except requests.exceptions.ConnectionError :
		pass

root = Tk()

root.title("Weathe_now")
root.bind("<Button-3>", right_click)

frame1_1 = Frame(root, bg="#FE9A2E", width=1, height=1)
frame1_1.pack(side=TOP, fill=X)

frame2_2 = Frame(root, bg="#F5ECCE",  width=1, height=1)
frame2_2.pack(expand=1, fill=BOTH)

frame3_3 = Frame(root, bg="#FE9A2E", width=1, height=40)
frame3_3.pack(side=BOTTOM, fill=X)

Upstate = Label(frame1_1, font=("Times 30", 22), text="Симферополь", bg="#FE9A2E")
Upstate.pack()

jWeather = Label(frame1_1, font=("Times 30", 12), bg="#FE9A2E")
jWeather.pack()

jText = Label(frame2_2, font=("Times 30", 48), bg="#F5ECCE")
jText.pack(expand=1)

right_click(1)
root.mainloop()