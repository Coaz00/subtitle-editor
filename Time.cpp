#include "Time.h"

#include <iostream>
using namespace std;

Time::Time()
{
	this->hh = this->mm = this->ss = this->ms = 0;
}

Time::Time(int hh, int mm, int ss, int ms)
{
	setTime(hh, mm, ss, ms);
}

void Time::setHours(int hh)
{
	this->hh = (hh >= 0 && hh <= 99) ? hh : 0;
}

void Time::setMinutes(int mm)
{
	this->mm = (mm >= 0 && mm <= 59) ? mm : 0;
}

void Time::setSeconds(int ss)
{
	this->ss = (ss >= 0 && ss <= 59) ? ss : 0;
}

void Time::setMiliSeconds(int ms)
{
	this->ms = (ms >= 0 && ms <= 999) ? ms : 0;
}

int Time::getHours()
{
	return this->hh;
}

int Time::getMinutes()
{
	return this->mm;
}

int Time::getSeconds()
{
	return this->ss;
}

int Time::getMiliSeconds()
{
	return this->ms;
}

void Time::setTime(int hh, int mm, int ss, int ms)
{
	setHours(hh);
	setMinutes(mm);
	setSeconds(ss);
	setMiliSeconds(ms);
}

Time * Time::getTime()
{
	return this;
}

int Time::readNumber(string subtitles, int & pos, char end)
{
	int number = 0;

	while (subtitles[pos] != end) {
		number = 10 * number + (subtitles[pos++] - '0');
	}
	pos++; // preskacemo znak end

	return number;
}

void Time::saveNumber(string& subtitles, int number,string type)
{
	string num;

	if (type == "else") {

		if (number == 0)
			num += "00";

		else {
			if (number < 10) {

				while (number > 0) {
					num += (number % 10 + '0');
					number = number / 10;
				}
				num += '0';
			}
			else {
				while (number > 0) {
					num += (number % 10 + '0');
					number = number / 10;
				}
			}
		}
	}

	else if (type == "ms") {
		if (number == 0) num += "000";

		else if(number < 10 ){
			while (number > 0) {
				num += (number % 10 + '0');
				number = number / 10;
			}
			num += "00";
		}
		else if (number >= 10 && number < 100) {
			while (number > 0) {
				num += (number % 10 + '0');
				number = number / 10;
			}
			num += '0';
		}
		else {
			while (number > 0) {
				num += (number % 10 + '0');
				number = number / 10;
			}
		}
	}

	for (int i = num.size() - 1; i >= 0; i--)
		subtitles += num[i];

}


void Time::readTime(string subtitles, int & pos, char end)
{
	setHours(readNumber(subtitles, pos, ':'));
	
	setMinutes(readNumber(subtitles, pos, ':'));
	
	setSeconds(readNumber(subtitles, pos, ','));
	
	setMiliSeconds(readNumber(subtitles, pos, end));
	
}

void Time::saveTime(string& subtitles)
{
	saveNumber(subtitles, this->hh, "else");
	subtitles += ':';
	saveNumber(subtitles, this->mm, "else");
	subtitles += ':';
	saveNumber(subtitles, this->ss, "else");
	subtitles += ',';
	saveNumber(subtitles, this->ms, "ms");
}

void Time::increaseTime(int ms)
{
	this->ms += ms;
	this->ss += this->ms / 1000;
	this->ms = this->ms % 1000;

	this->mm += this->ss / 60;
	this->ss = this->ss % 60;

	this->hh += this->mm / 60;
	this->mm = this->mm % 60;
}

void Time::decreaseTime(int ms)
{
	this->ms -= ms;
	if (this->ms >= 0) return;

	this->ss += this->ms / 1000;
	this->ss--;
	this->ms = 1000 + (this->ms % 1000);
	if (this->ms == 1000) {
		this->ms = 0;
		this->ss++;
	}

	if (this->ss >= 0) return;

	this->mm += this->ss / 60;
	this->mm--;
	this->ss = 60 + (this->ss % 60);
	if (this->ss == 60) {
		this->ss = 0;
		this->mm++;
	}

	if (this->mm >= 0) return;

	this->hh += this->mm / 60;
	this->hh--;
	this->mm = 60 + (this->mm % 60);
	if (this->mm == 60) {
		this->mm = 0;
		this->hh++;
	}
}

void Time::miliSecondsToTime(int ms)
{
	this->hh = this->mm = this->ss = this->ms = 0;
	increaseTime(ms);
}

int Time::timeToMiliSeconds()
{
	int mseconds = 0;
	
	mseconds += this->ms;
	mseconds += this->ss * 1000;
	mseconds += this->mm * 1000 * 60;
	mseconds += this->hh * 1000 * 60 * 60;

	return mseconds;
}

