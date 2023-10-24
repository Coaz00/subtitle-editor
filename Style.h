#ifndef STYLE_H
#define STYLE_H

class Style {
public:
	Style();

	int getStart();
	int getEnd();
	char getType();

	void setStart(int start);
	void setEnd(int end);
	void setType(int type);

private:
	int start;
	int end;
	char type;
};

typedef struct elem_style {
	Style* style;
	struct elem_style* next;
}ElemS;

#endif


