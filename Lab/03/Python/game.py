import threading
import time
import random
import math
import ui
import menu

BALL_COUNT = 3
ROW_COUNT = 5

def get_random_free_cell(root):
	free_cells = []
	for lst in root.cell:
		for x in lst:
			if x.ball == "none":
				free_cells += [x]
	if len(free_cells) == 0:
		return None
	else:
		return random.choice(free_cells)

def is_cell_exists(qmap, x, y):
	return		(x >= 0) and (y >= 0)\
			and (x < len(qmap)) and (y < len(qmap[0]))\

def is_cell_free(qmap, x, y):
		return		(x >= 0) and (y >= 0)\
			and (x < len(qmap)) and (y < len(qmap[0]))\
			and (qmap[x][y] == "none")

def get_back_path(root, graph, idx):
	i = idx
	cell = []
	while (idx >= 0):
		x = graph[idx][0]
		y = graph[idx][1]
		cell.insert(0, root.cell[x][y])
		idx = graph[idx][2]
	return cell

def search_path(root, cell_start, cell_end):
	destx = cell_end.x
	desty = cell_end.y
	map_size = len(root.cell)
	qmap = [map_size*[None] for x in range(map_size)]
	for i in range(map_size):
		for j in range(map_size):
			qmap[i][j] = root.cell[i][j].ball
	graph = [[cell_start.x, cell_start.y, -1]]
	i = 0
	while i < len(graph):
		x = graph[i][0]
		y = graph[i][1]
		qmap[x][y] = "searched"

		if (x == cell_end.x) and (y == cell_end.y):
			return get_back_path(root, graph, i)
			break;

		if is_cell_free(qmap, x+1, y):
			graph += [[x+1, y, i]]

		if is_cell_free(qmap, x, y+1):
			graph += [[x, y+1, i]]

		if is_cell_free(qmap, x-1, y):
			graph += [[x-1, y, i]]

		if is_cell_free(qmap, x, y-1):
			graph += [[x, y-1, i]]

		i += 1
	return None

def game_new_buffer(root):
	x = []
	for i in range(BALL_COUNT):
		x += [random.choice(ui.ball_colors)]
	root.next_balls = x
	menu.paint_buffer(root)

def check_row(root, posx, posy, func):
	if (posx < 0): posx = 0
	if (posy < 0): posy = 0
	if not is_cell_exists(root.cell, posx, posy):
		return None
	color = "none"
	rows_to_delete = []
	while is_cell_exists(root.cell, posx, posy):
		cell = root.cell[posx][posy]
		if len(rows_to_delete) == ROW_COUNT:
			return rows_to_delete
		if (cell.ball == "none") or (cell.ball != color): 
			color = cell.ball
			rows_to_delete = []
		posx, posy = func(posx, posy)
		rows_to_delete += [cell]
	if len(rows_to_delete) == ROW_COUNT:
		return rows_to_delete

def game_destroy_cells_proc(root, cell, do_step):
	for t in threading.enumerate(): # wait for animation
		if t.daemon:
			try:
				t.join()
			except:
				pass

	x = cell.x
	y = cell.y
	rez = []
	rez += [check_row(root, x-ROW_COUNT-1, y, lambda px, py: (px+1, py))]
	rez += [check_row(root, x, y-ROW_COUNT-1, lambda px, py: (px, py+1))]
	rez += [check_row(root, x-min(x, y, ROW_COUNT-1), y-min(x, y, ROW_COUNT-1), lambda px, py: (px+1, py+1))]
	rez += [check_row(root, x+min(len(root.cell)-x-1, y, ROW_COUNT-1), y-min(len(root.cell)-x-1, y, ROW_COUNT-1), lambda px, py: (px-1, py+1))]
	for x in rez:
		if x == None: continue
		ui.clear_cell(root, x, True)
		root.score += 10
		menu.refresh_score(root)
		return
	if do_step: game_step(root)

def game_destroy_cells(root, cell, do_step):
	t = threading.Thread(target=game_destroy_cells_proc, args=(root, cell, do_step,))
	t.daemon = True
	t.start()

def game_over(root):
	menu.show_game_over_text(root)

def game_step_draw_proc(root, cell, selected, ball_size,\
					animation, only_visual_change):
	for t in threading.enumerate(): # wait for animation
		if t.daemon:
			try:
				t.join()
			except:
				pass

	for x in cell:
		ui.draw_cell(root, [x], selected = selected, ball = x.ball, ball_size = ball_size,\
					animation = animation, only_visual_change = only_visual_change)
		game_destroy_cells(root, x, False)
	if get_random_free_cell(root) == None:
		game_over(root)

def game_step(root):
	cells = []
	if root.next_balls == None:
		game_new_buffer(root)
	for i in range(BALL_COUNT):
		cell = get_random_free_cell(root)
		if cell == None:
			break
		cell.ball = root.next_balls[i]
		cells += [cell]
	t = threading.Thread(target=game_step_draw_proc, args=(root, cells, False, 0,\
				True, False))
	t.daemon = True
	t.start()
	#for i in range(len(cells)):
	#	game_destroy_cells(root, cells[i], False)
	game_new_buffer(root)