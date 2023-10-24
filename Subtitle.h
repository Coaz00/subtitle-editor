#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "Time.h"
#include<string>
#include "Style.h"
using namespace std;

#define NOT_INIT -1

class Subtitle {
public:
	Subtitle();
	~Subtitle();

	void setIndex(int ind);
	void setStart(int ms);
	void setEnd(int ms);
	void setText(string txt);
	void setSelected(bool sel);
	void setStylesFirst(ElemS* first);
	void setStylesLast(ElemS* last);

	int getIndex();
	Time* getStart();
	Time* getEnd();
	string getText();
	bool getSelected();
	ElemS* getStylesFirst();
	ElemS* getStylesLast();

	void loadSubtitle(string subtitles, int& pos);
	void saveSubtitle(string& subtitles);

	void deleteStyles();

	void shiftForward(int ms);
	void shiftBackward(int ms);

	void changeLine(int& pos, int max);

	int duration();
	int numOfWords();
	string splitText(int numWords, int& pos);

private:
	int index;
	Time* start;
	Time* end;
	string text;
	bool selected;
	ElemS* stylesFirst;
	ElemS* stylesLast;


	int readNumber(string subtitles, int& pos, char end);
	void readText(string subtitles, int& pos);

	void saveNumber(string& subtitles, int number);
	void saveText(string& subtitles, string txt);

	void sortStyles(ElemS* first);
};

#endif