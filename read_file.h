#ifndef READ_FILE_H
#define READ_FILE_H

#endif //READ_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p, int dl, int pr) {
		creation_time = c;
		duration = d;
		period = p;
		deadline = dl;
		priority = pr;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os <<
			"Creation time = " << p.creation_time <<
				" duration = " << p.duration <<
					" period = " << p.period <<
						" deadline = " << p.deadline <<
							" priority = " << p.priority <<	endl;
		return os;
	}

	int getCreationTime() const {
		return creation_time;
	}

	int getDuration() const {
		return duration;
	}

	int getPeriod() const {
		return period;
	}

	int getDeadline() const {
		return deadline;
	}

	int getPriority() const {
		return priority;
	}

	
private:	
	int creation_time;
	int duration; //seconds
	int period; //seconds
	int deadline; //seconds
	int priority;
};

class File
{

public:
	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
		// cada processo tem 5 atributos:
		// a: data de criacao
		// b: duracao
		// c: periodo
		// d: deadline
		// e: prioridade estatica (3 > 2 para RM)
		int a, b, c, d, e;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c >> d >> e) {
			auto *p = new ProcessParams(a, b, c, d, e);
			processes.push_back(p);
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		auto iter = processes.begin();

		for(; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}

	~File() {
		for(auto p : processes) {
				delete p;
		}
	}

	vector<ProcessParams *> get_processes() {
		return processes;
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};

// main movido para main.cpp
// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// 	// return 0;
// }

