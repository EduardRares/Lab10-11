#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include <QWidget>

using namespace std;

class Observer : public QWidget
{
public:
	virtual void update(string str) = 0;
	string mesaj;
};

class somewindow : public Observer	
{
	void update(string str) override {
		;
	}
};

class mainWindow : public Observer
{
	void update(string str) override;
};


class Observable
{
	vector<Observer*> observers;
	public:
		void addObserver(Observer* obs) { observers.push_back(obs); }
		void removeObserver(Observer* obs) { observers.erase(remove(observers.begin(), observers.end(), obs), observers.end()); }
		void notify(string str)
		{
			for (auto o : observers)
				o->update(str);
		}
};
#endif // !OBSERVER_H
