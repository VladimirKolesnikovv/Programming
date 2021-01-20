from tkinter import *
from PIL import Image, ImageTk

def image_load(filename, cropx1 = 0, cropy1 = 0, cropx2 = 0, cropy2 = 0, w = 0, h = 0):
	x = Image.open("./data/"+filename).convert("RGBA")
	if cropx2+cropy2 > 0:
		x = x.crop((cropx1, cropy1, cropx2, cropy2))
	if w+h > 0:
		x = x.resize((w, h), Image.ANTIALIAS)
	return x

def image_render(obj, img):
	obj.img = img;
	obj.image = ImageTk.PhotoImage(img)
	obj.configure(image=obj.image)

def label_render(obj, img): #Canvas Only
	obj.update()
	obj.img = Image.new("RGBA", (obj.winfo_reqwidth(), obj.winfo_reqheight()));
	obj.img = image_compasite(obj.img, img, -obj.winfo_x(), -obj.winfo_y())
	obj.image = ImageTk.PhotoImage(obj.img)
	obj.create_image(0, 0, image=obj.image, anchor=NW)
	obj.create_text(0, 0, text=obj.text, font=obj.font, anchor="nw",
                          fill=obj.fontcolor)

def canvas_render(obj, img, img_background):
	obj.update() 
	obj.img = image_compasite(img, img_background, 0, 0)
	obj.img = image_compasite(obj.img, img, 0, 0)
	obj.image = ImageTk.PhotoImage(obj.img)
	obj.create_image(0, 0, image=obj.image, anchor=NW)

def image_compasite(bottom_img, top_img, x, y):
	top_upscale_img = Image.new("RGBA", bottom_img.size)
	top_upscale_img.paste(top_img, (x, y))
	return Image.alpha_composite(bottom_img, top_upscale_img)