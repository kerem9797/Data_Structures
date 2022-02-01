#include<iostream>              
#include<fstream>
#include<sstream>
#define STADÝUMCAPACÝTY 50000
using namespace std;
struct node {
	string name, surname;
	int seatNumber;
	string gender;
	int ticketPrice;
	struct node* next;
	struct node* prev;
};
struct node* head = NULL;
struct stack {
	int behindTheGoal;
	int sideOfTheStadium;
	int quantity;
	struct node* top;
};
stack* stk;
void stackInitialize(stack* stk) {
	stk->behindTheGoal = 0;
	stk->sideOfTheStadium = 0;
	stk->quantity = 0;
	stk->top = NULL;
}
bool isFullStk(stack* stk) {
	return(stk->quantity == STADÝUMCAPACÝTY);
}
bool isEmptyStk(stack* stk) {
	return(stk->quantity == 0);
}
void pushSpectator(stack* stk, int audience) {
	system("cls");
	struct node* spectator = new node();
	spectator->seatNumber = audience;
	if (isFullStk(stk)) {
		cout << "The stadium is full of spectators,there aren't any empty seats" << endl;
	}
	else if (isEmptyStk(stk)) {
		stk->top = spectator;
		stk->top->next = NULL;
		stk->top->prev = NULL;
		stk->quantity++;
		if (0<audience &&audience <= STADÝUMCAPACÝTY * 0.4) {
			stk->behindTheGoal++;
		}
		else if(STADÝUMCAPACÝTY * 0.4 < audience && audience <= STADÝUMCAPACÝTY) {
			stk->sideOfTheStadium++;
		}
		else {
			cout << "You entered the wrong seat number" << endl;
		}
		cout << "Number of spectators behind the goal:" << stk->behindTheGoal << endl;
		cout << "Number of spectators on the side of the stadium:" << stk->sideOfTheStadium << endl;
	}
	else {
		spectator->next = stk->top;
		stk->top = spectator;
		spectator->prev = spectator->next;
		stk->quantity++;
		if (0<audience &&audience <= STADÝUMCAPACÝTY * 0.4) {
			stk->behindTheGoal++;
		}
		else if(STADÝUMCAPACÝTY * 0.4 < audience && audience <= STADÝUMCAPACÝTY) {
			stk->sideOfTheStadium++;
		}
		else {
			cout << "You entered the wrong seat number" << endl;
		}
		cout << "Number of spectators behind the goal:" << stk->behindTheGoal << endl;
		cout << "Number of spectators on the side of the stadium:" << stk->sideOfTheStadium << endl;
	}
}
struct queue {
	int quantity;
	struct node* front;
	struct node* rear;
};
queue* q;
void queueInitialize(queue* q) {
	q->quantity = 0;
	q->front = q->rear = NULL;
}
bool isFullQ(queue* q) {
	return(q->quantity == STADÝUMCAPACÝTY);
}
bool isEmptyQ(queue* q) {
	return(q->quantity == 0);
}
void enqueue(queue* q,string name,int seatNumber) {
	system("cls");
	struct node* spectator = new node();
	spectator->name = name;
	spectator->seatNumber =seatNumber;
	if (isFullQ(q)) {
		cout << "Queue is full,no audience can enter the stadium" << endl;
	}
	else if (isEmptyQ(q)) {
		spectator->next = NULL;
		spectator->prev = NULL;
		q->rear = q->front = spectator;
		q->quantity++;
		cout << name << " entranced the queue" << endl;
	}
	else {
		spectator->next = q->rear;
		spectator->prev = q->front;
		q->rear = spectator;
		q->quantity++;
		cout << name << " entranced the queue" << endl;
	}
}
void dequeue(queue* q) {
	system("cls");
	if (isEmptyQ(q)) {
		cout << "Queue is empty" << endl;
	}
	else if (q->quantity == 1) {
		string name = q->front->name;
		int seatNumber = q->front->seatNumber;
		delete q->front;
		q->front = NULL;
		q->rear = NULL;
		q->quantity--;
		cout << name << " with " << seatNumber << " number took ticket and left the queue" << endl;
	}
	else {
		struct node* temp = q->rear;
		while (temp->next != q->front) {
			temp = temp->next;
		}
		string name = q->front->name;
		int seatNumber = q->front->seatNumber;
		delete q->front;
		q->front = temp;
		q->front->next = NULL;
		q->quantity--;
		cout << name << " with " << seatNumber << " number took ticket and left the queue" << endl;
	}
}
void showQueue(queue* q) {
	system("cls");
	if (isEmptyQ(q)) {
		cout << "Queue is empty" << endl;
	}
	else {
		struct node* temp = q->rear;
		while (temp->next !=NULL) {
			cout << temp->name<<"(" << temp->seatNumber<<")"<< "-->";
			temp = temp->next;
		}
		cout << temp->name<<"("<< temp->seatNumber <<")"<< " " << endl;
	}
}
void addSpectator(string name, string surname, int seatNumber, string gender, int ticketPrice) {
	system("cls");
	struct node* spectator = new node();
	spectator->name = name;
	spectator->surname = surname;
	spectator->seatNumber = seatNumber;
	spectator->gender = gender;
	spectator->ticketPrice = ticketPrice;
	if (head == NULL) {
		head = spectator;
		head->next = NULL;
		head->prev = NULL;
		cout <<"The first spectator with "<<seatNumber<< " seat number entered the stadium." << endl;
	}
	else {
		spectator->next = head;
		head->prev = spectator;
		head = spectator;
		head->prev = NULL;
		cout << "The spectator with " << seatNumber << " seat number entered the stadium." << endl;
	}
}
void takeOutTheSpectator(int seatNumber) {
	system("cls");
	bool result = false;
	if (head == NULL) {
		cout << "Stadium is empty,there isn't any spectator" << endl;
		result = true;
	}
	else {
		if (head->next == NULL && head->seatNumber == seatNumber) {
			delete head;
			head = NULL;
			cout << "The spectator with " << seatNumber << " number left the stadium" << endl;
			result = true;
		}
		else if (head->next != NULL && head->seatNumber == seatNumber) {
			struct node* temp = head->next;
			delete head;
			head = temp;
			head->prev = NULL;
			cout << "The spectator with " << seatNumber << " number left the stadium" << endl;
			result = true;
		}
		else {
			struct node* temp = head;
			while (temp->next != NULL) {
				if (temp->seatNumber == seatNumber) {
					struct node* temp2 = temp->prev;
					struct node* temp3 = temp->next;
					delete temp;
					temp2->next = temp3;
					temp3->prev = temp2;
					cout << "The spectator with " << seatNumber << " number left the stadium" << endl;
					result = true;
					break;
				}
				temp = temp->next;
			}
			if (temp->seatNumber == seatNumber) {
				struct node* temp2 = temp->prev;
				delete temp;
				temp2->next = NULL;
				cout << "The spectator with " << seatNumber << " number left the stadium" << endl;
				result = true;
			}
		}
	}
	if (!result)
		cout << "There isn't any spectator in stadium with " << seatNumber << " number" << endl;
}
void print() {
	system("cls");
	if (head == NULL) {
		cout << "There isn't any spectator in the stadium" << endl;
	}
	else {
		struct node* temp = head;
		while (temp->next != NULL) {
			cout <<"Name:" << temp->name << endl <<"Surname:" << temp->surname << endl <<"Seat Number:"<< temp->seatNumber << endl <<"Gender:" << temp->gender << endl <<"Ticket Price:" << temp->ticketPrice << "$" << endl;
			temp = temp->next;
			cout << "-------------------------------------" << endl;
		}
		cout << "Name:" << temp->name << endl << "Surname:" << temp->surname << endl << "Seat Number:" << temp->seatNumber << endl << "Gender:" << temp->gender << endl << "Ticket Price:" << temp->ticketPrice << "$" << endl;
	}
}
void amountOfSpectators() {
	system("cls");
	int amount = 0;
	if (head == NULL) {
		cout << "The stadium is empty" << endl;
	}
	else {
		struct node* temp = head;
		while (temp->next != NULL) {
			amount++;
			temp = temp->next;
		}
		amount++;
		cout << "The capacity of stadium is " << STADÝUMCAPACÝTY << endl;
		cout << "There are total " << amount << " spectators in the stadium" << endl;
		cout << "There are still " << STADÝUMCAPACÝTY - amount << " empty seats in the stadium" << endl;
	}
}
void totalFee() {
	system("cls");
	int total = 0;
	if (head == NULL) {
	  cout << "No tickets sold,there aren't any money" << endl;
	}
	else{
		struct node* temp = head;
		while (temp->next != NULL) {
			total += temp->ticketPrice;
			temp = temp->next;
		}
		total += temp->ticketPrice;
		cout << "Total fee of ticket prices are:" << total <<"$" << endl;
	}
}
void writeToFile() {
	system("cls");
	if (head == NULL) {
		cout << "The list is empty" << endl;
	}
	else {
		ofstream write("stadium.txt", ios::app);
		struct node* temp = head;
		while (temp->next != head) {
			write << temp->name << " " <<temp->surname << " " << temp->seatNumber << " " << temp->gender << " " << temp->ticketPrice << endl;
			temp = temp->next;
		}
		write << temp->name << " " << temp->surname << " " << temp->seatNumber << " " << temp->gender << " " << temp->ticketPrice << endl;
		write.close();
		cout << "'stadium.txt' registered to the file" << endl;
	}
}
void readFromFile() {
	system("cls");
	cout << "The file is reading..." << endl;
	ifstream read("stadium.txt", ios::app);
	string line;
	while (getline(read, line)) {
		cout << line << " " << endl;
	}
	cout << "--------------------------------" << endl;
	read.close();
}
int main() {
	stack stk;
	stackInitialize(&stk);
	queue qu;
	queueInitialize(&qu);
	int ticketPrice, choice, seatNumber;
	string name, surname;
	string gender;
	while (1) {
		cout << endl;
		cout << "Information about stadium and stadium entrance" << endl;
		cout << "1-Add audience" << endl;
		cout << "2-Take out the audience" << endl;
		cout << "3-Show information about audience" << endl;
		cout << "4-Amount of audience in the stadium" << endl;
		cout << "5-Total ticket prices" << endl;
		cout << "6-Information about audience tribune" << endl;
		cout << "7-Add to queue" << endl;
		cout << "8-Remove from the queue" << endl;
		cout << "9-Show the people who are waiting in queue" << endl;
		cout << "10-Save to file" << endl;
		cout << "11-Read from file" << endl;
		cout << "0-EXIT" << endl;
		cin >> choice;
		switch (choice) {
		case 1: cout << "Enter information about audience:" << endl;
			cout << "Name:"; cin >> name;
			cout << "Surname:"; cin >> surname;
			cout << "Seat Number(Between 0 and Stadium Capacity):"; cin >> seatNumber;
			cout << "Gender:"; cin >> gender;
			cout << "Ticket Price:"; cin >> ticketPrice;
			addSpectator(name, surname, seatNumber, gender, ticketPrice);
			break;
		case 2: cout << "Enter the seat number of the audience to be removed from stadium:"; cin >> seatNumber;
			takeOutTheSpectator(seatNumber);
			break;
		case 3: print();
			break;
		case 4: amountOfSpectators();
			break;
		case 5: totalFee();
			break;
		case 6: cout << "Enter the spectators seat number:"; cin >> seatNumber;
			pushSpectator(&stk, seatNumber);
			break;
		case 7:cout << "Name:"; cin >> name;
			cout << "Seat Number:"; cin >> seatNumber;
			enqueue(&qu, name, seatNumber);
			break;
		case 8: dequeue(&qu);
			break;
		case 9: showQueue(&qu);
			break;
		case 10: writeToFile();
			break;
		case 11: readFromFile();
			break;
		case 0: cout << "It's exiting from the program..." << endl;
			return 0;
			break;
		}
	}
	return 0;
}