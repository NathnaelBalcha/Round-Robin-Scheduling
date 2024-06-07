#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
struct Process {
	int Process_ID;
	int Arrival_Time;
	int Service_Time;
	int Remaining_Time;
};
bool First_Time_In = true;
int Chart_Time, Time_Line, Total_Time = 0, Default_Error = 1, Input_Error = 2,
    Reinput_fail = 0, Input_check = 0;
void Header()
{
	cout << "\n\t\t\t   MEKELLE UNIVERSITY\n";
	cout << "\t\tETHIOPIAN INSTITUTE OF TECHNOLOGY (EIT-M)\n";
	cout << "\t\t     DEPARTMENT OF COMPUTER SCIENCE\n";
	cout << "\t\t         AND INFORMATION SYSTEM\n";
	cout << "\t\t      OPERATING SYSTEMS (CoSo3023) \n\n";
}
void Error_Message()
{
	system("cls");
	Header();
	cout << " \t   Alert /!\\" << endl;
	cout << " ---------------------------------\n";
	cout << " You have used unknown keyword! \n";
	cout << " Peace choose the correct keyword.";
	cout << "\n ---------------------------------\n\n";
}
void Input_Error_Message()
{
	system("cls");
	Header();
	cout << " \t   Alert /!\\" << endl;
	cout << " -----------------------------------\n";
	cout << " Input mis much exception! \n";
	cout << " Peace enter valid number.";
	cout << "\n -----------------------------------\n\n";
}
void Input_Error_Checker(int Type_of_Error_Message)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		if (Type_of_Error_Message == Default_Error)
		{
			Error_Message();
		}
		else if (Type_of_Error_Message == Input_Error)
		{
			Input_Error_Message();
		}
		Reinput_fail = 1;
	}
}
void GanttChart(int Quantum,int Number_of_Processes,vector<Process> processes ) {
	cout << "\n\n -----------------------------------------\n";
	cout << "   Gantt Chart";
	cout << "\n -----------------------------------------\n\n";
	int Time_Array[Number_of_Processes], Process_Time[Time_Line], index = 0;
	for (int i = 0; i < Number_of_Processes; ++i) {
		Time_Array[i] = processes[i].Service_Time;
	}
	while (index < Number_of_Processes) {
		Time_Array[index] = ( Time_Array[index] - Quantum );
		Time_Line++;
		if (Time_Array[index] <= 0) {
			index++;
		}
	}
	for (int i = 0; i < Time_Line; ++i) {
		if (First_Time_In) {
			cout << "    ------";
			First_Time_In = false;
		} else {
			cout << "-----";
		}
	}
	First_Time_In = true;
	cout << endl;
	int i;
	while (true) {
		bool allFinished = true;
for (auto& process : processes) {
			if (process.Remaining_Time > 0) {
				allFinished = false;
				int Execute_Time;
				Execute_Time = min(Quantum, process.Remaining_Time);
				if (First_Time_In) {
					cout << "    | P" << process.Process_ID << " |";
					First_Time_In = false;
				} else {
					cout << " P" << process.Process_ID << " |";
				}
				Total_Time += Execute_Time;
				Process_Time[i] = Total_Time;
				process.Remaining_Time -= Execute_Time;
				i++;
			}
		}
		if (allFinished)
			break;
	}
	First_Time_In = true;
	cout << endl;
	for (int i = 0; i < Time_Line; ++i) {
		if (First_Time_In) {
			cout << "    ------";
			First_Time_In = false;
		} else {
			cout << "-----";
		}
	}
	First_Time_In = true;
	cout << endl;
	for (int i = -1; i < Time_Line; ++i) {
		if (First_Time_In) {
			cout << "    '    ";
			First_Time_In = false;
		} else {
			cout << "'    ";
		}
	}
	First_Time_In = true;
	cout << endl;
	for (int i = -1; i < Time_Line; ++i) {
		if (First_Time_In) {
			cout << "    0    ";
			First_Time_In = false;
		} else {
			Chart_Time += Quantum;
			if (Chart_Time <= 10) {
				cout << Process_Time[i] << "    ";
			} else {
				cout << Process_Time[i] << "   ";
			}
		}
	}
	First_Time_In = true;
	cout << endl;
}
void Calculate_Average_Wait_Time(int Number_of_Processes,vector<Process> processes) {
	int Total_Wait_Time = 0;
for (const auto& process : processes) {
		int Wait_Time = max(0, Total_Time - process.Arrival_Time - process.Service_Time);
		Total_Wait_Time += Wait_Time;
	}
	double Average_Wait_Time = static_cast<double>(Total_Wait_Time) / Number_of_Processes;
	cout << "\n\t Average wait time: " << Average_Wait_Time << endl;
}
int main() {
	int Looping_Choice,
    	DoRe = 0, MeRe = 0,
	    Current_Time = 0, Counter_of_Process = 1,
	    Number_of_Processes, Quantum;
	do {
		Header();
		do {
			do {
				Reinput_fail = 0;
				cout << "   Round Robin";
		        cout << "\n ------------------------------------\n";
				cout << " Enter the Number of Processes: ";
				cin >> Number_of_Processes;
				Input_Error_Checker(Input_Error);
			} while (Reinput_fail == 1);
			Input_check = 0;
			if (Number_of_Processes < 1)
			{
				system("cls");
				Header();
				cout << " \t   Alert /!\\" << endl;
				cout << " -------------------------------------\n";
				cout << " You need to have at least one process";
				cout << "\n -------------------------------------\n\n";
				Input_check = 1;
			}
		} while (Input_check == 1);
		system("cls");
		Header();
		do {
			do {
				Reinput_fail = 0;
				cout << "   Round Robin";
		        cout << "\n ------------------------------------\n";
				cout << " Enter the Quantum Time: ";
				cin >> Quantum;
				Input_Error_Checker(Input_Error);
			} while (Reinput_fail == 1);
			Input_check = 0;
			if (Quantum < 1)
			{
				system("cls");
				Header();
				cout << " \t   Alert /!\\" << endl;
				cout << " -------------------------------------\n";
				cout << " The Quantum must be above 0";
				cout << "\n -------------------------------------\n\n";
				Input_check = 1;
			}
		} while (Input_check == 1);
		vector<Process> processes(Number_of_Processes);
		system("cls");
		Header();
		// Input process details
		for (int i = 0; i < Number_of_Processes; ++i) {
			do {
				do {
					do {
						do {
							Reinput_fail = 0;
							cout << "   Round Robin";
		                    cout << "\n ------------------------------------\n";
							cout << " Enter Details for Process " << Counter_of_Process << ":" << endl;
							processes[i].Process_ID = i + 1;
							cout << "  Arrival Time: ";
							cin >> processes[i].Arrival_Time;
							Input_Error_Checker(Input_Error);
						} while (Reinput_fail == 1);
						Input_check = 0;
						if (processes[i].Arrival_Time < 0)
						{
							system("cls");
							Header();
							cout << " \t   Alert /!\\" << endl;
							cout << " -------------------------------------\n";
							cout << " The Arrival Time can't be negative";
							cout << "\n -------------------------------------\n\n";
							Input_check = 1;
						}
					} while (Input_check == 1);
					cout << "  Service Time: ";
					cin >> processes[i].Service_Time;
					Input_Error_Checker(Input_Error);
				} while (Reinput_fail == 1);
				Input_check = 0;
				if (processes[i].Service_Time < 1)
				{
					system("cls");
					Header();
					cout << " \t   Alert /!\\" << endl;
					cout << " -------------------------------------\n";
					cout << " The Service Time must be above 1";
					cout << "\n -------------------------------------\n\n";
					Input_check = 1;
				}
			} while (Input_check == 1);
			processes[i].Remaining_Time = processes[i].Service_Time;
			Counter_of_Process++;
			system("cls");
			Header();
		}
		Counter_of_Process = 1;
		cout << "   Round Robin Using Quantum " << Quantum << " sec.";
		cout << "\n -----------------------------------------\n\n";
		cout << "    Process   Arrival Time   ServiceTime";
		int Display_Process, Display_Arrival_Time, Display_Service_Time;
		for (int i = 0; i < Number_of_Processes; ++i) {
			Display_Process = processes[i].Process_ID;
			Display_Arrival_Time = processes[i].Arrival_Time;
			Display_Service_Time = processes[i].Service_Time;
			cout << "\n       " << Display_Process << "\t    " << Display_Arrival_Time << "\t\t  " << Display_Service_Time;
		}
		GanttChart(Quantum, Number_of_Processes,processes);
		Calculate_Average_Wait_Time(Number_of_Processes, processes);
		Reinput_fail = 0;
		do {
			Reinput_fail = 0;
			cout << "\n---------------------------------------------\n";
			cout << " 0 To Exist the Program";
			cout << "\n---------------------------------------------\n";
			cout << " Enter your Choice ";
			cin >> Looping_Choice;
			Input_Error_Checker(Default_Error);
		}while (Reinput_fail == 1);
		if (Looping_Choice == 0)
		{
			DoRe = 0;
			MeRe = 0;
		}
		else
		{
			system("cls");
			Error_Message();
			DoRe = 1;
		}
	}
	while (MeRe == 1);
	return 0;
}

