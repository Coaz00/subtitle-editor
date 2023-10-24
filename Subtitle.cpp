#include "Subtitle.h"

#include <iostream>
using namespace std;

Subtitle::Subtitle()
{
	this->text = "";
	this->index = 0;
	this->start = new Time();
	this->end = new Time();
	this->start->setTime(0, 0, 0, 0);
	this->end->setTime(0, 0, 0, 0);
	this->selected = false;
	this->stylesFirst = this->stylesLast = nullptr;
}

Subtitle::~Subtitle()
{
	delete this->start;
	delete this->end;
	deleteStyles();
}

void Subtitle::setIndex(int ind)
{
	this->index = ind;
}

void Subtitle::setStart(int ms)
{
	this->start->setTime(0, 0, 0, 0);
	this->start->increaseTime(ms);
}

void Subtitle::setEnd(int ms)
{
	this->end->setTime(0, 0, 0, 0);
	this->end->increaseTime(ms);
}

void Subtitle::setText(string txt)
{
	this->text = txt;
}

void Subtitle::setSelected(bool sel)
{
	this->selected = sel;
}

void Subtitle::setStylesFirst(ElemS* first)
{
	this->stylesFirst = first;
}

void Subtitle::setStylesLast(ElemS* last)
{
	this->stylesLast = last;
}

int Subtitle::getIndex()
{
	return this->index;
}

Time* Subtitle::getStart()
{
	return this->start->getTime();
}

Time* Subtitle::getEnd()
{
	return this->end->getTime();
}

string Subtitle::getText()
{
	return this->text;
}

bool Subtitle::getSelected()
{
	return this->selected;
}

ElemS* Subtitle::getStylesFirst()
{
	return this->stylesFirst;
}

ElemS* Subtitle::getStylesLast()
{
	return this->stylesLast;
}

int Subtitle::readNumber(string subtitles, int & pos, char end)
{
	int number = 0;

	while (subtitles[pos] != end) {
		number = 10 * number + (subtitles[pos++] - '0');
	}
	pos++; // preskacemo znak end

	return number;
}


void Subtitle::readText(string subtitles, int & pos)
{
	while (!((subtitles[pos - 1] == '\n') && (subtitles[pos] == '\n'))) {
		
		if (subtitles[pos] == '<' && subtitles[pos + 1] != '/') {
			int tmpPos = pos;

			ElemS* tmp = new ElemS;
			tmp->next = nullptr;
			tmp->style = new Style();

			if (subtitles[tmpPos + 1] != '/') {
				tmp->style->setType(subtitles[tmpPos + 1]);
				tmp->style->setStart(this->text.size());
			}

			while (!((subtitles[tmpPos] == '<') && (subtitles[tmpPos + 1] == '/'))) tmpPos++;
			tmp->style->setEnd(tmp->style->getStart() + tmpPos - pos - 3);

			if (this->stylesFirst == nullptr) this->stylesFirst = this->stylesLast = tmp;

			else {
				this->stylesLast->next = tmp;
				this->stylesLast = tmp;
			}
			
			pos += 3;
		}

		else if (subtitles[pos] == '<' && subtitles[pos + 1] == '/') pos += 4;
		else this->text += subtitles[pos++];

	}

	pos++; // preskacemo prazan red, prelazimo na sl titl
}

void Subtitle::deleteStyles()
{
	ElemS* old;
	while (this->stylesFirst != nullptr) {
		old = this->stylesFirst;
		this->stylesFirst = this->stylesFirst->next;
		delete old;
	}
}


void Subtitle::shiftForward(int ms)
{
	this->start->increaseTime(ms);
	this->end->increaseTime(ms);
}

void Subtitle::shiftBackward(int ms)
{
	this->start->decreaseTime(ms);
	this->end->decreaseTime(ms);
}

void Subtitle::changeLine(int& pos, int max)
{
	int count = 0;
	while (this->text[pos] != '\n') {
		if (text[pos] != ' ') count++;
		if (count > max) {
			while (this->text[pos] != ' ') pos--;
			this->text[pos] = '\n';
			pos++;
			return;
		}
		pos++;
	}
	pos++;

}

int Subtitle::duration()
{
	return (this->end->timeToMiliSeconds() - this->start->timeToMiliSeconds());
}

int Subtitle::numOfWords()
{
	int words = 0;
	for (int i = 0; i < this->text.size(); i++) {
		if (this->text[i] == ' ' || this->text[i] == '\n') words++;
	}
	return words;
}

void Subtitle::sortStyles(ElemS* first)
{
	for(ElemS* i = first; i != nullptr; i = i = i->next)
		for (ElemS* j = i; j != nullptr; j = j->next) 
			if (i->style->getStart() > j->style->getStart()) {
				Style* tmp = i->style;
				i->style = j->style;
				j->style = tmp;
			}
		
}


void Subtitle::saveNumber(string& subtitles,  int number)
{
	string num;

	while (number > 0) {
		num += (number % 10 + '0');
		number = number / 10;
	}


	for (int i = num.size() - 1; i >= 0; i--)
		subtitles += num[i];
	
}

void Subtitle::saveText(string& subtitles, string txt)
{
	sortStyles(this->stylesFirst);

	ElemS* curr = this->stylesFirst;

	if (this->stylesFirst == nullptr) {
		for (int i = 0; i < txt.size(); i++)
			subtitles += txt[i];
	}
	else {
		for (int i = 0; i < txt.size(); i++) {
			if (i == curr->style->getStart()) {
				subtitles += "<";
				subtitles += curr->style->getType();
				subtitles += ">";
			}


			else if (i == curr->style->getEnd()) {
				subtitles += "<";
				subtitles += "/";
				subtitles += curr->style->getType();
				subtitles += ">";
				if (curr->next != nullptr) curr = curr->next;
			}
			subtitles += txt[i];
		}
	}
}

void Subtitle::loadSubtitle(string subtitles, int& pos)
{
	this->index = readNumber(subtitles, pos, '\n');
	this->start->readTime(subtitles, pos, ' ');
	pos += 4; // preskacemo --> i razmak
	this->end->readTime(subtitles, pos, '\n');
	readText(subtitles, pos);
}

void Subtitle::saveSubtitle(string& subtitles)
{
	saveNumber(subtitles, this->index);
	subtitles += '\n';
	this->start->saveTime(subtitles);
	subtitles += ' ';
	subtitles += '-';
	subtitles += '-';
	subtitles += '>';
	subtitles += ' ';
	this->end->saveTime(subtitles);
	subtitles += '\n';
	saveText(subtitles, this->text);
}

string Subtitle::splitText(int numWords, int& pos) {
	string textSplit;
	string word;
	for (int i = 0; i < numWords; i++) {
		while (this->text[pos] != ' ' && this->text[pos] != '\n') {
			word += this->text[pos++];
		}
		textSplit += word;
		textSplit += this->text[pos];
		if (this->text[pos] == '\n' && this->text[pos++] == '\n') break;
		else pos++;
		word = "";
	}
	return textSplit;
}


