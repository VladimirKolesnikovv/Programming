from ui import *

def repaint(root):
	pass #do nothing (???)

def resize_event(event):
	if hasattr(event.widget, "ui"):
		repaint(event.widget);

root = init_ui()
root.bind("<Configure>", resize_event)
root.mainloop()