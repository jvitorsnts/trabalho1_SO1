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
		os << "Creation time = " << p.creation_time <<
		" duration = " << p.duration <<
		" period = " << p.period <<
		" deadline = " << p.deadline <<
		" priority = " << p.priority <<
		endl;
		return os;
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
		// cada processo tem 5 parametros:
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
			ProcessParams *p = new ProcessParams(a, b, c, d, e);
			processes.push_back(p);
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}

	~File() {
		for(int i = 0; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};

int main()
{
	File f;
	f.read_file();
	f.print_processes_params();
	// we read the file and print the processes parameters
	return 0;
}

