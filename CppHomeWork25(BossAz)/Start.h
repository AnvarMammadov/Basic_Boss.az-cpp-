#pragma once
#include<iostream>
#include<Windows.h>
#include "Entities.h"
using namespace std;
void ShowIntro();

void Start() {
	while (true)
	{
		ShowIntro();
		system("cls");
	}
}
int w_count = 2;
Worker** workers = new Worker * [w_count] {
	new Worker{ new char[30] {"elvin123"},new char[30] {"Elvin"}
		,new char[30] {"Programmer"},NULL,NULL,NULL },
		new Worker{ new char[30] {"john26"},new char[30] {"John"}
			,new char[30] {"UI/UX Designer"},NULL,NULL,NULL },
};


int e_count = 1;
Employer** employers = new Employer * [e_count] {
	new Employer{ new char[30] {"rafiq123"},new char[30] {"Rafiq Eliyev"},
	new char[30] {"Rafiq MMC"},NULL,NULL
	}
};

Employer* getEmployerByUsername(const char* username) {
	for (size_t i = 0; i < e_count; i++)
	{
		if (strcmp(employers[i]->username, username) == 0) {
			return employers[i];
		}
	}
	return nullptr;
}

void ShowEmployerMenu() {
	cout << "Add advertisement 1 : " << endl;
	cout << "Show appliers     2 : " << endl;
}

int global_id = 0;

AD* GetNewAD() {
	cin.ignore();
	cin.clear();
	cout << "Enter advertisement title " << endl;
	char* title = new char[100] {};
	cin.getline(title, 100);
	cout << "Enter salary " << endl;
	double salary = 0;
	cin >> salary;
	++global_id;
	AD* ad = new AD{ global_id,title,salary };
	return ad;
}
void AddADToEmployer(Employer* employer, AD* ad) {
	auto temp = new AD * [employer->count + 1] {};
	for (size_t i = 0; i < employer->count; i++)
	{
		temp[i] = employer->ads[i];
	}temp[employer->count] = ad;
	employer->ads = temp;
	temp = nullptr;
	employer->count++;
}

Worker* GetWorkerByUsername(const char* username) {
	for (size_t i = 0; i < w_count; i++)
	{
		if (strcmp(workers[i]->username, username) == 0) {
			return workers[i];
		}
	}
	return nullptr;
}
void ShowWorkerMenu(const Worker* worker) {
	cout << "Advertisements 1 : " << endl;
	cout << "Create your own CV 2 : " << endl;//task
	cout << "Notifications(" << worker->count << ")   3 : " << endl;
	cout << "Observe your cv 4 : " << endl;//task
}


void ShowEmployerAD(Employer* employer) {
	for (size_t i = 0; i < employer->count; i++)
	{
		cout << "=========ADS=============" << endl;
		cout << "ID : " << employer->ads[i]->id << endl;
		cout << "TITLE : " << employer->ads[i]->title << endl;
		cout << "SALARY : " << employer->ads[i]->salary << "$" << endl;
	}
}

void ShowAllAds() {
	for (size_t i = 0; i < e_count; i++)
	{
		ShowEmployerAD(employers[i]);
	}
}
CV* CreateCV() {
	cout << "Enter salary : ";
	double salary = 0;
	cin >> salary;
	cout << "Enter Experience : ";
	int experience = 0;
	cin >> experience;
	cin.clear();
	cin.ignore();
	cout << "Enter languages : ";
	char* languages = new char[100];
	cin.getline(languages, 100);
	cout << "Enter about : ";
	char* about = new char[200];
	cin.getline(about, 200);
	CV* cv = new CV{ salary,experience,languages,about };
	return cv;
}
void AddCVToWorker(Worker* worker, CV* cv) {
	worker->cv = cv;
	cv = nullptr;
}
void ShowYourCv(Worker* worker) {
	cout << "Name : " << worker->fullname << endl;
	cout << "Specialty : " << worker->speciality << endl;
	cout << "Salary : " << worker->cv->salary << endl;
	cout << "Experience : " << worker->cv->experience << endl;
	cout << "Languages : " << worker->cv->languages << endl;
	cout << "About : " << worker->cv->about << endl;
}
void ShowIntro() {
	cout << "==============" << endl;
	cout << "Worker(w) or Employer(e)" << endl;
	char select = ' ';
	cin >> select;
	if (select == 'w') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username = new char[100] {};
		cin.getline(username, 100);

		auto worker = GetWorkerByUsername(username);
		if (worker != nullptr) {
			ShowWorkerMenu(worker);
			int select = 0;
			cin >> select;
			if (select == 1) {
				ShowAllAds();
				system("pause");
			}
			else if (select == 2) {
				auto cv=CreateCV();
				AddCVToWorker(worker, cv);
			}
			else if (select== 4) {
				ShowYourCv(worker);
				system("pause");
			}
		}
		else {
			cout << "Not found" << endl;
			system("color 4");
			system("pause");
			system("color 7");
		}
	}
	else if (select == 'e') {
		cin.ignore();
		cin.clear();
		cout << "Enter username : " << endl;
		char* username = new char[50] {};
		cin.getline(username, 50);

		auto employer = getEmployerByUsername(username);
		if (employer != nullptr) {
			ShowEmployerMenu();
			int select = 0;
			cin >> select;
			if (select == 1) {
				auto ads = GetNewAD();
				AddADToEmployer(employer, ads);
			}
		}
		else {
			cout << "Not found" << endl;
			system("color 4");
			system("pause");
			system("color 7");
		}
	}
	else {
		cout << "Invalid selection" << endl;
	}

}

