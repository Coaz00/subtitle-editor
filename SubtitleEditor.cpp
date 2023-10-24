#include "SubtitleEditor.h"

#include<iostream>
using namespace std;



SubtitleEditor::SubtitleEditor()
{
	this->first = this->last = nullptr;
	this->stack = new Stack();
}

SubtitleEditor::SubtitleEditor(string subtitles)
{
	loadSubtitles(subtitles);
}

SubtitleEditor::~SubtitleEditor()
{
	deleteSequence(this->first);
	stack->deleteStack();
	delete stack;
}

int SubtitleEditor::loadSubtitles(string subtitles)
{
	if(this->first != nullptr) deleteSequence(this->first);

	int pos = 0;

	while(1) {
		//kreiranje i incijalizacija elementa liste
		Elem* tmp = new Elem;
		tmp->sub = new Subtitle();
		tmp->next = nullptr;
		
		//ucitavnje titla
		tmp->sub->loadSubtitle(subtitles, pos);
		

		//ulancavanje elementa u listu
		if (this->first == nullptr)
			this->first = this->last = tmp;
		else {
			this->last->next = tmp;
			this->last = tmp;
		}
		
		//provera da li je doslo do kraja sekvence
		if (subtitles[pos] == '\0') return -1;
	}
	
}

string SubtitleEditor::saveSubtitles()
{
	string subtitles;

	Elem* curr = this->first;

	while (curr != nullptr) {
		curr->sub->saveSubtitle(subtitles);
		subtitles += '\n';
		curr = curr->next;
	}

	delete curr;

	return subtitles;
}

void SubtitleEditor::addToSelection(int start, int end)
{

	if (start < 1 || start > this->last->sub->getIndex()) start = 1;
	if (end > this->last->sub->getIndex() || end < 1) end = this->last->sub->getIndex();

	Elem* curr = this->first;

	while (curr->sub->getIndex() != start) curr = curr->next;

	for (int i = 0; i <= end - start; i++) {
		curr->sub->setSelected(true);
		curr = curr->next;
	}
	curr = nullptr;
	delete curr;
}

void SubtitleEditor::deselect()
{

	Elem* curr = this->first;

	while (curr != nullptr) {
		curr->sub->setSelected(false);
		curr = curr->next;
	}

	delete curr;
}
void SubtitleEditor::boldText(int start, int end)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;
	while (curr != nullptr) {
		if (curr->sub->getSelected()) {
			ElemS* tmp = new ElemS;

			tmp->next = nullptr;
			tmp->style = new Style();

			tmp->style->setType('b');
			if (start < 0 || start > curr->sub->getText().size()) tmp->style->setStart(0);
			else tmp->style->setStart(start);
			if (end < 0 || end > curr->sub->getText().size()) tmp->style->setEnd(curr->sub->getText().size()-1);
			else tmp->style->setEnd(end-1);
			

			if (curr->sub->getStylesFirst() == nullptr) {
				curr->sub->setStylesFirst(tmp);
				curr->sub->setStylesLast(tmp);
			}
			else {
				curr->sub->getStylesLast()->next = tmp;
				curr->sub->setStylesLast(tmp);
			}

		}
		curr = curr->next;
	}

	delete curr;
}

void SubtitleEditor::italicText(int start, int end)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;
	while (curr != nullptr) {
		if (curr->sub->getSelected()) {
			ElemS* tmp = new ElemS;

			tmp->next = nullptr;
			tmp->style = new Style();

			tmp->style->setType('i');
			if (start < 0 || start > curr->sub->getText().size()) tmp->style->setStart(0);
			else tmp->style->setStart(start);
			if (end < 0 || end > curr->sub->getText().size()) tmp->style->setEnd(curr->sub->getText().size() - 1);
			else tmp->style->setEnd(end - 1);


			if (curr->sub->getStylesFirst() == nullptr) {
				curr->sub->setStylesFirst(tmp);
				curr->sub->setStylesLast(tmp);
			}
			else {
				curr->sub->getStylesLast()->next = tmp;
				curr->sub->setStylesLast(tmp);
			}

		}
		curr = curr->next;
	}

	delete curr;
}

void SubtitleEditor::underlineText(int start, int end)
{

	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;
	while (curr != nullptr) {
		if (curr->sub->getSelected()) {
			ElemS* tmp = new ElemS;

			tmp->next = nullptr;
			tmp->style = new Style();

			tmp->style->setType('u');
			if (start < 0 || start > curr->sub->getText().size()) tmp->style->setStart(0);
			else tmp->style->setStart(start);
			if (end < 0 || end > curr->sub->getText().size()) tmp->style->setEnd(curr->sub->getText().size() - 1);
			else tmp->style->setEnd(end - 1);


			if (curr->sub->getStylesFirst() == nullptr) {
				curr->sub->setStylesFirst(tmp);
				curr->sub->setStylesLast(tmp);
			}
			else {
				curr->sub->getStylesLast()->next = tmp;
				curr->sub->setStylesLast(tmp);
			}

		}
		curr = curr->next;
	}

	delete curr;
}


void SubtitleEditor::removeStyle()
{

	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;

	while (curr != nullptr) {
		if (curr->sub->getSelected()) {
			curr->sub->deleteStyles();
		}
		curr = curr->next;
	}

	delete curr;
}
void SubtitleEditor::shiftForward(int ms)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr;

	if (selectionExists()) {
		curr = this->first;
		while (curr != nullptr) {
			if (curr->sub->getSelected()) {
				curr->sub->shiftForward(ms);
			}
			curr = curr->next;
		}
	}
	else {
		curr = this->first;
		while (curr != nullptr) {
			curr->sub->shiftForward(ms);
			curr = curr->next;
		}
	}
	delete curr;
}
void SubtitleEditor::shiftBackward(int ms)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr;

	if (selectionExists()) {
		curr = this->first;
		while (curr != nullptr) {
			if (curr->sub->getSelected()) {
				curr->sub->shiftBackward(ms);
			}
			curr = curr->next;
		}
	}
	else {
		curr = this->first;
		while (curr != nullptr) {
			curr->sub->shiftBackward(ms);
			curr = curr->next;
		}
	}
	delete curr;
}
void SubtitleEditor::deleteSequence(Elem * head)
{
	while (head != nullptr) {
		Elem* old = head;
		head = head->next;
		delete old->sub;
		delete old;
	}
	this->first = this->last  = nullptr;
}

void SubtitleEditor::insertSubtitle(int start, int length, string text)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr, * prev;
	curr = this->first;
	prev = nullptr;

	Elem* tmp = new Elem;
	tmp->next = nullptr;
	tmp->sub = new Subtitle();
	tmp->sub->setStart(start);
	tmp->sub->setEnd(start + length);
	tmp->sub->setText(text);

	if (curr == nullptr) { //prazna lista
		this->first = tmp;
	}

	while (curr != nullptr) {
		if (curr->sub->getStart()->timeToMiliSeconds() > start) {
			if (prev != nullptr) { //ako se dodaje u sredini
				prev->next = tmp;
				tmp->next = curr;
				tmp->sub->setIndex(prev->sub->getIndex() + 1);
			}
			else { // ako se dodaje na pocetak
				tmp->next = this->first;
				this->first = tmp;
			}
			break;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}

	if (curr == nullptr) { // ako se dodaje na kraj, prev moze biti nullptr samo ako je lista prazna, a taj slucaj je obradjen gore
		if(prev != nullptr) prev->next = tmp;
		this->last = tmp;
	}
	while (curr != nullptr) { // azuriranje indeksa
		curr->sub->setIndex(curr->sub->getIndex() + 1);
		curr = curr->next;
	}
	curr = prev = nullptr;
	delete curr;
	delete prev;
}

void SubtitleEditor::undo()
{
	if (stack->getHead() == nullptr) return;

	loadSubtitles(stack->getPreviousState());
	stack->removeFromStack();
}

int SubtitleEditor::selectionExists()
{
	Elem* curr = this->first;
	while (curr != nullptr) {
		if (curr->sub->getSelected()) return 1;//selekcija postoji
		curr = curr->next;
	}
	delete curr;
	return 0;//selekcija ne postoji
}

void SubtitleEditor::deleteSubtitles()
{

	this->stack->addToStack(this->saveSubtitles());

	if (!selectionExists()) return; // ako ne postoji selekcija, izlazimo iz funkcije
	
	Elem* curr, * prev, * tmp;
	curr = this->first;
	prev = nullptr;

	while (curr != nullptr) {
		if (curr->sub->getSelected()) {
			
			if (prev != nullptr) { // opsti slucaj
				prev->next = curr->next;
				Elem* old = curr;
				curr = curr->next;
				delete old;
			}
			else { //pocetak
				Elem* old = curr;
				curr = curr->next;
				this->first = curr;
				delete old;
			}
			tmp = curr;
			while (tmp != nullptr) { // azuriranje indeksa
				tmp->sub->setIndex(tmp->sub->getIndex() - 1);
				tmp = tmp->next;
			}
			delete tmp;

		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	prev = nullptr;
	delete curr;
	delete prev;
	
}

void SubtitleEditor::merge(string subtitles)
{
	this->stack->addToStack(this->saveSubtitles());

	SubtitleEditor* additionalSub = new SubtitleEditor();
	additionalSub->loadSubtitles(subtitles);

	if (last != nullptr) this->last->next = additionalSub->first;
	else this->first = additionalSub->first;

	Elem* curr = additionalSub->first;
	while (curr != nullptr && last != nullptr) {
		curr->sub->setIndex(curr->sub->getIndex() + last->sub->getIndex());
		curr = curr->next;
	}

	this->last = additionalSub->last;

	//delete additionalSub;
	
}

void SubtitleEditor::fixLongLines(int max)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;
	if (selectionExists()) {
		while (curr != nullptr) {
			if (curr->sub->getSelected()) {
				int pos = 0;
				while (pos < curr->sub->getText().size()) curr->sub->changeLine(pos, max);
			}
			curr = curr->next;
		}
	}
	else {
		while (curr != nullptr) {
			int pos = 0;
			while (pos < curr->sub->getText().size()) {
				curr->sub->changeLine(pos, max);
			}
			curr = curr->next;
		}
	}
	delete curr;
}

void SubtitleEditor::fixLongTime(int ms)
{
	this->stack->addToStack(this->saveSubtitles());

	Elem* curr = this->first;
	Elem* prev = nullptr;
	Elem* target;
	int pos = 0;
	if (selectionExists()) {
		while (curr != nullptr) {
			int numSplit = 1;
			if (curr->sub->getSelected()) {
				if (curr->sub->duration() > ms) {
					numSplit = curr->sub->duration() / ms + 1;
					int numOfWordsSplit = curr->sub->numOfWords() / numSplit + 1;
					int durationSplit = curr->sub->duration() / numSplit;
					target = curr;
					for (int i = 0; i < numSplit; i++) {
						if (prev == nullptr) {
							Elem* tmp = new Elem;
							tmp->next = curr->next;
							tmp->sub = new Subtitle();
							tmp->sub->setText(target->sub->splitText(numOfWordsSplit, pos));
							tmp->sub->setIndex(curr->sub->getIndex());
							tmp->sub->setStart(target->sub->getStart()->timeToMiliSeconds());
							tmp->sub->setEnd(target->sub->getStart()->timeToMiliSeconds() + durationSplit);
							this->first = tmp;
							curr = tmp;
						}
						else {
							Elem* tmp = new Elem;
							tmp->next = curr->next;
							if (i != 0) {
								curr->next = tmp;
								prev = curr;
								curr = tmp;
							}
							tmp->sub = new Subtitle();
							tmp->sub->setText(target->sub->splitText(numOfWordsSplit, pos));
							tmp->sub->setIndex(prev->sub->getIndex() + 1);
							if (i == 0) tmp->sub->setStart(target->sub->getStart()->timeToMiliSeconds());
							else  tmp->sub->setStart(prev->sub->getEnd()->timeToMiliSeconds());
							tmp->sub->setEnd(tmp->sub->getStart()->timeToMiliSeconds() + durationSplit);

							if (i == 0) {
								prev->next = tmp;
								curr = tmp;
							}
							
						}
					}
					delete target;
				}
			}
			prev = curr;
			curr = curr->next;
			pos = 0;

			if (numSplit != 1) {
				Elem* help = curr;
				while (help != nullptr) {
					help->sub->setIndex(help->sub->getIndex() + numSplit - 1);
					help = help->next;
				}
				delete help;
			}
		}
		prev = nullptr;
		delete curr;
		delete prev;
	}
	else {
		while (curr != nullptr) {
				if (curr->sub->duration() > ms) {
					int numSplit = curr->sub->duration() / ms + 1;
					int numOfWordsSplit = curr->sub->numOfWords() / numSplit + 1;
					int durationSplit = curr->sub->duration() / numSplit;
					target = curr;
					for (int i = 0; i < numSplit; i++) {
						if (prev == nullptr) {
							Elem* tmp = new Elem;
							tmp->next = curr->next;
							tmp->sub = new Subtitle();
							tmp->sub->setText(target->sub->splitText(numOfWordsSplit, pos));
							tmp->sub->setIndex(curr->sub->getIndex());
							tmp->sub->setStart(target->sub->getStart()->timeToMiliSeconds());
							tmp->sub->setEnd(target->sub->getStart()->timeToMiliSeconds() + durationSplit);
							this->first = tmp;
							curr = tmp;
						}
						else {
							Elem* tmp = new Elem;
							tmp->next = curr->next;
							if (i != 0) {
								curr->next = tmp;
								prev = curr;
								curr = tmp;
							}
							tmp->sub = new Subtitle();
							tmp->sub->setText(target->sub->splitText(numOfWordsSplit, pos));
							tmp->sub->setIndex(prev->sub->getIndex() + 1);
							if (i == 0) tmp->sub->setStart(target->sub->getStart()->timeToMiliSeconds());
							else  tmp->sub->setStart(prev->sub->getEnd()->timeToMiliSeconds());
							tmp->sub->setEnd(tmp->sub->getStart()->timeToMiliSeconds() + durationSplit);

							if (i == 0) {
								prev->next = tmp;
								curr = tmp;
							}

						}
					}
					delete target;
				}
			
			prev = curr;
			curr = curr->next;
			pos = 0;
		}
		prev = nullptr;
		delete curr;
		delete prev;
	}
}
