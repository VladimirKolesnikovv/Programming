import threading
from tkinter import *
from PIL import Image, ImageTk
from imgutils import *
from game import *
import ui

def hide_game_over_text(root):
	root.label_gameover.text = ""
	label_render(root.label_gameover, root.ui.img)

def show_game_over_text(root):
	root.label_gameover.text = "Игра окончена"
	label_render(root.label_gameover, root.ui.img)

def refresh_score(root):
	root.label_score.text = "Счёт: "+str(root.score)
	label_render(root.label_score, root.ui.img)

#bug with disappearing
def repaint_menu(root): #force repaint
	root.update()
	old_geometry = root.winfo_geometry()
	root.geometry("100x100")
	root.update()
	root.geometry(old_geometry)
	root.update()

def button_newgame_on_click(event, root):
	t = threading.Thread(target=ui.new_game, args=(root,))
	t.daemon = True
	t.start()

def paint_buffer(root):
	txs = root.textures
	buff = root.next_balls
	img = Image.new(mode = "RGBA", size = (120, 50))
	x = 0
	for ball_color in buff:
		img = image_compasite(img, txs["ball-"+ball_color+"-4"], x-16, -16)
		x += 38
	canvas_render(root.canvas_help, img, root.ui.img)

def draw_menu(root):
	root.label_header = Canvas(root.ui, bd=0, highlightthickness=0, width=120, height=30)
	root.label_header.text = "Lines"
	root.label_header.font = ("Helvetica", 18)
	root.label_header.fontcolor = "white"
	root.label_header.place(x=600, y=40)
	label_render(root.label_header, root.ui.img)

	root.label_score = Canvas(root.ui, bd=0, highlightthickness=0, width=180, height=30)
	root.label_score.text = "Счёт: 0"
	root.label_score.font = ("Helvetica", 18)
	root.label_score.fontcolor = "white"
	root.label_score.place(x=600, y=90)
	label_render(root.label_score, root.ui.img)

	root.button_step = Button(root.ui, text="Сделать ход", bg="#606060", activebackground="#505050", fg="#D1D1C0", activeforeground="#D1D1C0", width=12)
	root.button_step.place(x=600, y=150)
	root.button_step.bind("<Button-1>", lambda event: game_step(root))

	root.label_help = Canvas(root.ui, bd=0, highlightthickness=0, width=120, height=30)
	root.label_help.text = "Подсказка:"
	root.label_help.font = ("Helvetica", 14)
	root.label_help.fontcolor = "#AAAAAA"
	root.label_help.place(x=600, y=210)
	label_render(root.label_help, root.ui.img)

	root.canvas_help = Canvas(root.ui, bd=0, highlightthickness=0, width=120, height=30)
	root.canvas_help.text = ""
	root.canvas_help.font = ("Helvetica", 14)
	root.canvas_help.fontcolor = "#AAAAAA"
	root.canvas_help.place(x=600, y=240)

	root.button_newgame = Button(root.ui, text="Новая игра", bg="#606060", activebackground="#505050", fg="#D1D1C0", activeforeground="#D1D1C0", width=16, height=2)
	root.button_newgame.place(x=600, y=290)
	root.button_newgame.bind("<Button-1>", lambda event: button_newgame_on_click(event, root))

	root.label_gameover = Canvas(root.ui, bd=0, highlightthickness=0, width=180, height=30)
	root.label_gameover.text = ""
	root.label_gameover.font = ("Helvetica", 16)
	root.label_gameover.fontcolor = "white"
	root.label_gameover.place(x=600, y=360)
	label_render(root.label_gameover, root.ui.img)