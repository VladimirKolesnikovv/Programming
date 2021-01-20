import threading
import time
from tkinter import *
from PIL import Image, ImageTk
from imgutils import *
from menu import *
from game import *

ANIM_TAIL_ENABLED = True
ANIM_TAIL_COUNT = 7
ANIM_BLOWUP_ENABLED = True
ANIM_FADEOUT_ENABLED = True
ANIM_SPEED = 30
CELL_MARGIN = 21
CELL_DISTANCE = 62
FIELD_SIZE = 9

ball_colors = ["aqua", "blue", "green", "pink", "red", "violet", "yellow"]

def load_textures():
	txs = {}
	# background #
	txs.update({"page-bgr": image_load("page-bgr.png")})
	# ball #
	for ball_id in range(7):
		ball_name = "ball-"+ball_colors[ball_id]
		ball_file = ball_name+".png"
		for ball_size in range(7):
			ball_fname = ball_name+"-"+str(ball_size)
			txs.update({ball_fname: image_load(ball_file, 0, 59*ball_size, 55, 59*ball_size+59)})
	# cell #
	txs.update({"cell-bgr-0": image_load("cell-bgr.png", 0, 0, 69, 68, 62, 62)})
	txs.update({"cell-bgr-1": image_load("cell-bgr.png", 0, 69, 69, 137, 62, 62)})
	return txs
 
def draw_background(root, resname):
	root.ui = Label(root, width=root.winfo_width(), height=root.winfo_height())
	root.ui.pack(fill=NONE, expand=1)
	txs = root.textures
	screen_width = root.winfo_width()
	screen_height = root.winfo_height()
	bgr = Image.new("RGBA", (screen_width, screen_height))
	bgr_width, bgr_height = txs[resname].size
	for i in range(0, screen_width, bgr_width):
		for j in range(0, screen_height, bgr_height):
			bgr = image_compasite(bgr, txs[resname], i, j)
	image_render(root.ui, bgr)

def animation_proc(root, animtype, listcell):
	if animtype == "blowup":
		for i in range(6, -1, -1):
			for cell in listcell:
				draw_cell(root, [cell], cell.selected, cell.ball, i, False, True);
			time.sleep(1/ANIM_SPEED)
	if animtype == "tail":
		ball_name = listcell[0].animball
		start_animation(root, "fadeout", [listcell[0]])
		stack = []
		for cell in listcell:
			if (cell == listcell[0]):
				continue
			if len(stack)+1 > ANIM_TAIL_COUNT:
				draw_cell(root, [stack[-1]], stack[-1].selected, "none", 0, False, True);
				stack.pop(-1)
			stack.insert(0, cell)
			if (cell == listcell[-1]):
				draw_cell(root, [stack[0]], stack[0].selected, ball_name, 0, True, True);
			else:
				draw_cell(root, [stack[0]], stack[0].selected, ball_name, 6, False, True);
			time.sleep(1/ANIM_SPEED)
		for cell_id in range(len(stack)-1, 0, -1):
			cell = stack[cell_id]
			draw_cell(root, [cell], cell.selected, "none", 0, False, True);
			time.sleep(1/ANIM_SPEED)
	if animtype == "fadeout":
		for i in range(6):
			for cell in listcell:
				draw_cell(root, [cell], cell.selected, cell.animball, i, False, True);
			time.sleep(1/ANIM_SPEED)
		for cell in listcell:
			draw_cell(root, [cell], cell.selected, "none", 0, False, True);


def start_animation(root, animtype, listcell):
	t = threading.Thread(target=animation_proc, args=(root, animtype, listcell,))
	t.daemon = True
	t.start()

def draw_cell(root, cells, selected=False, ball = "none", ball_size = 0, animation = False, only_visual_change = False):
	txs = root.textures
	for cell_item in cells:
		if only_visual_change == False:
			cell_item.ball = ball
			cell_item.ball_size = ball_size
			cell_item.selected = selected
		if (selected):
			image_render(cell_item, txs["cell-bgr-1"])
		else:
			image_render(cell_item, txs["cell-bgr-0"])
	if (ball != "none"):
		if (ANIM_BLOWUP_ENABLED and animation):
			start_animation(root, "blowup", cells)
		else:
			for cell_item in cells:
				bgr = image_compasite(cell_item.img, txs["ball-"+ball+"-"+str(ball_size)], 3, 2)
				image_render(cell_item, bgr)

def select_cell(root, cell, selected):
	cell.selected = selected
	if (selected):
		root.selected = cell
	draw_cell(root, [cell], selected, cell.ball, cell.ball_size, False)

def clear_cell(root, cells, animation = False):
	txs = root.textures
	for cell_item in cells:
		cell_item.animball = cell_item.ball
		cell_item.ball = "none"
		cell_item.selected = False
	if (ANIM_FADEOUT_ENABLED and animation):
		start_animation(root, "fadeout", cells)
	else:
		for cell_item in cells:
			image_render(cell_item, txs["cell-bgr-0"])

def move_cell(root, cells, animation = False):
	txs = root.textures
	cell1 = cells[0]
	cell1.animball = cell1.ball
	cell1.ball = "none"
	cell1.selected = False
	cell2 = cells[-1]
	cell2.ball = cell1.animball
	cell2.selected = False
	if (ANIM_TAIL_ENABLED and animation):
		start_animation(root, "tail", cells)
	else:
		draw_cell(root, [cell1], cell1.selected, cell1.ball, 0, True)
		draw_cell(root, [cell2], cell2.selected, cell2.ball, 0, True)

def cell_on_click(event, root):
	if (event.widget.ball != "none"):
		if (root.selected != None):
			select_cell(root, root.selected, False)
		select_cell(root, event.widget, True)
	else:
		if (root.selected != None):
			path = search_path(root, root.selected, event.widget)
			if path == None: return
			move_cell(root, path, True)
			game_destroy_cells(root, event.widget, True)
			#game_step(root)
			root.selected = None

def init_cells(root):
	txs = root.textures
	root.cell = [FIELD_SIZE*[None] for x in range(FIELD_SIZE)]
	for i in range(FIELD_SIZE):
		for j in range(FIELD_SIZE):
			cell_item = Label(root.ui, borderwidth=0)
			cell_item.place(x=CELL_DISTANCE*i+CELL_MARGIN, y=CELL_DISTANCE*j+CELL_MARGIN)
			root.cell[i][j] = cell_item
			root.cell[i][j].selected = False
			root.cell[i][j].ball = "none"
			root.cell[i][j].x = i
			root.cell[i][j].y = j
			root.cell[i][j].bind("<Button-1>", lambda event: cell_on_click(event, root))
			draw_cell(root, [root.cell[i][j]], False, "none", 0)

def new_game(root):
	root.score = 0
	root.selected = None
	root.next_balls = None
	init_cells(root)
	game_step(root)
	menu.refresh_score(root)
	menu.hide_game_over_text(root)
	repaint_menu(root) #fix disappearing bug

def init_ui():
	root = Tk()
	root.resizable(False, False)
	root.geometry("800x600")
	root.update()
	root.title("Lines")
	root.textures = load_textures()
	draw_background(root, "page-bgr") #LOAD ROOT.UI
	draw_menu(root)
	new_game(root)
	return root