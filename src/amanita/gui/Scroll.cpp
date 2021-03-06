
#include "../_config.h"
#include <amanita/gui/Image.h>
#include <amanita/gui/Scroll.h>
#include <amanita/gui/Icon.h>



namespace a {
namespace gui {

Object_Inheritance(Scroll,Widget)


Scroll::_settings Scroll::_s = { 0 };

Scroll::Scroll(int id,int x,int y,int w,int h,int st) : Widget(x,y,w,h) {
	// Object::setInstance(Scroll::Class);
	setID(id);
	val = min = 0,max = 100,inc = 10;
	bmin = new Icon(0);
	bmin->setActionListener(this);
	add(bmin);
	bmax = new Icon(1);
	bmax->setActionListener(this);
	add(bmax);
	bslide = new Icon(2);
	bslide->setImage(_s.img,_s.slide.plain,_s.slide.active,_s.slide.down,_s.slide.disabled);
	bslide->setLocked(false);
	bslide->setActionListener(this);
	bslide->setMouseMotionListener(this);
	add(bslide);
	setStyle(st);
	ae = (ActionEvent){ this,0 };
}

Scroll::~Scroll() {}

void Scroll::setDefaultSettings(Image *img,uint32_t data[22]) {
	_s = (_settings){
		img,
		{ img->getCell(data[0]),(int)data[0],(int)data[1],(int)data[2],(int)data[3] },
		{ img->getCell(data[4]),(int)data[4],(int)data[5],(int)data[6],(int)data[7] },
		{ img->getCell(data[8]),(int)data[8],(int)data[9],(int)data[10],(int)data[11] },
		{ img->getCell(data[12]),(int)data[12],(int)data[13],(int)data[14],(int)data[15] },
		{ img->getCell(data[16]),(int)data[16],(int)data[17],(int)data[18],(int)data[19] },
		img->getCell(data[20]),img->getCell(data[21])
	};
}

void Scroll::setStyle(int st) {
	style = st;
	if(style&SCROLL_HORIZ) {
		bmin->setImage(_s.img,_s.left.plain,_s.left.active,_s.left.down,_s.left.disabled);
		bmin->setLocation(getX(),getY()+(style&SCROLL_TOP? 0 : getHeight()-bmin->getHeight()));
		bmax->setImage(_s.img,_s.right.plain,_s.right.active,_s.right.down,_s.right.disabled);
		bmax->setLocation(getX()+getWidth()-bmax->getWidth(),getY()+(style&SCROLL_TOP? 0 : getHeight()-bmax->getHeight()));
		bar = _s.hbar;
		slide.x = bmin->getWidth();
		if(style&SCROLL_TOP) slide.y = 0;
		else slide.y = getHeight()-bslide->getHeight();
		slide.w = getWidth()-bmin->getWidth()-bmax->getWidth();
		slide.h = _s.hbar->h;
	} else {
		bmin->setImage(_s.img,_s.up.plain,_s.up.active,_s.up.down,_s.up.disabled);
		bmin->setLocation(getX()+(style&SCROLL_LEFT? 0 : getWidth()-bmin->getWidth()),getY());
		bmax->setImage(_s.img,_s.down.plain,_s.down.active,_s.down.down,_s.down.disabled);
		bmax->setLocation(getX()+(style&SCROLL_LEFT? 0 : getWidth()-bmax->getWidth()),getY()+getHeight()-bmax->getHeight());
		bar = _s.vbar;
		if(style&SCROLL_LEFT) slide.x = 0;
		else slide.x = getWidth()-bslide->getWidth();
		slide.y = bmin->getHeight();
		slide.w = _s.vbar->w;
		slide.h = getHeight()-bmin->getHeight()-bmax->getHeight();
	}
	positionSlide();
}
void Scroll::setValues(int v,int mn,int mx,int i) {
	min = mn,max = mx,inc = i,val = v<min? min : (v>max? max : v);
	positionSlide();
	if(actionListener) actionListener->actionPerformed(ae);
}
void Scroll::setValue(int v) {
	val = v<min? min : (v>max? max : v);
	positionSlide();
	if(actionListener) actionListener->actionPerformed(ae);
}

void Scroll::positionSlide() {
	int x,y;
	if(style&SCROLL_HORIZ) {
		x = getX()+bmin->getWidth()+((val-min)*slide.w)/max,y = getY()+slide.y;
		if(x<getX()+slide.x) x = getX()+slide.x;
		else if(x>getX()+slide.x+slide.w-bslide->getWidth())
			x = getX()+slide.x+slide.w-bslide->getWidth();
	} else {
		x = getX()+slide.x,y = getY()+bmin->getHeight()+((val-min)*slide.h)/max;
		if(y<getY()+slide.y) y = getY()+slide.y;
		else if(y>=getY()+slide.y+slide.h-bslide->getHeight())
			y = getY()+slide.y+slide.h-bslide->getHeight();
	}
	bslide->setLocation(x,y);
}

bool Scroll::mouseDrag(MouseMotionEvent &mme) {
	if(mme.source==bslide) {
		int v,x,y;
		if(style&SCROLL_HORIZ) {
			x = bslide->getX(),y = getY()+slide.y;
			if(x<getX()+slide.x) x = getX()+slide.x;
			else if(x>getX()+slide.x+slide.w-bslide->getWidth())
				x = getX()+slide.x+slide.w-bslide->getWidth();
		} else {
			x = getX()+slide.x,y = bslide->getY();
			if(y<getY()+slide.y) y = getY()+slide.y;
			else if(y>=getY()+slide.y+slide.h-bslide->getHeight())
				y = getY()+slide.y+slide.h-bslide->getHeight();
		}
		bslide->setLocation(x,y);

		if(style&SCROLL_HORIZ)
			v = min+((bslide->getX()-(getX()+slide.x))*(max-min))/(slide.w-bslide->getWidth());
		else v = min+((bslide->getY()-(getY()+slide.y))*(max-min))/(slide.h-bslide->getHeight());
		if(v<min) v = min;
		else if(v>max) v = max;

		if(v!=val) {
			val = v;
			if(actionListener) actionListener->actionPerformed(ae);
		}
		return true;
	}
	return false;
}

bool Scroll::actionPerformed(ActionEvent &ae) {
	if(ae.source==bmin || ae.source==bmax) {
		int v = val;
		if(ae.source==bmin) {
			v -= inc;
			if(v<min) v = min;
		} else {
			v += inc;
			if(v>max) v = max;
		}
		if(v!=val) {
			val = v;
			positionSlide();
			if(actionListener) actionListener->actionPerformed(this->ae);
		}
		return true;
	}
	return false;
}

void Scroll::paint(time_t time) {
	_s.img->draw(getX()+slide.x,getY()+slide.y,slide.w,slide.h,*bar);
}

}; /* namespace gui */
}; /* namespace a */


