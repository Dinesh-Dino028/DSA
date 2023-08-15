#include <iostream>

using namespace std;

class ArrayList {
#define MAXSIZE 50
	int a[MAXSIZE];
	int size = 0;
public:
	void insertAtEnd(int val) {
		a[size++] = val;
	}
	void insertAtPost(int pos, int val) {
		if (size == MAXSIZE) {
			cout << "Invalid Position";
		} else {
			for (int i = size-1; i >= pos; i--)
			{
				a[i+1] = a[i];
			}
			a[pos] = val;
			size++;
            cout<< "Inserted at position: "<<pos<<" val: "<<val;
		}
	}
	void deleteAtPos(int pos) {
        int i;
        int del = a[pos];
		if (size <= 0) {
			cout << "Invalid Position";
		} else {
			for(i=pos; i<size; i++) {
                a[i]=a[i+1];
            }
            size--;
		}
        cout<<"Deleted at position: "<<pos<<" val: "<<del;
	}
	void display() {
		for (int var = 0; var <= size-1; var++) {
			cout << a[var]<<" ";
		}
	}
};

int main() {
	int choice, pos, val;
	ArrayList a;
	while (true) {
		cout << "\n ----------------List Menu---------------- \n";
		cout << "1.Insert at the end \n";
		cout << "2.Insert at the position \n";
		cout << "3.Delete at the position \n";
		cout << "4.Display \n";
		cout << "5.Exit \n";
        cout<<"-------------------------------------------------\n";
        cout<< "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter value to insert: \n";
			cin >> val;
			a.insertAtEnd(val);
			break;
		case 2:
			cout << "Enter position at insert: \n";
			cin >> pos;
			cout << "Enter Value: \n";
			cin >> val;
			a.insertAtPost(pos, val);
			break;
		case 3:
			cout << "Enter position at delete: \n";
			cin >> pos;
			a.deleteAtPos(pos);
			break;
		case 4:
			cout<<"Array List values: ";
			a.display();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "Invalid Choice";
			break;
		}
	}
}
