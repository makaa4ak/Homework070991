#include <iostream>
#include "USERNAME.h"
#include "fstream"
#include <cstring>

using namespace std;

errno_t code;

const int MAX = 20;


/*
char* name;
char* surname;
char* work_pfone;
char* personal_phone;
*/

//email = new char[strlen(buff) + 1];
//strcpy_s(email, strlen(buff) + 1, buff);


USERNAME::USERNAME()
{
	name = nullptr;
	surname = nullptr;
	work_pfone = nullptr;
	personal_phone = nullptr;
    index = 0;
}
USERNAME::~USERNAME()
{
	delete[] name;
	delete[] surname;
	delete[] work_pfone;
	delete[] personal_phone;
}

void USERNAME::ShowUserData(const char* filename, USERNAME* user)
{
	FILE* users;
	code = fopen_s(&users, filename, "r");
	if (!code)
	{
		char buff;
		while ((buff = fgetc(users)) != EOF)
			cout << buff;
	}
	else {
		cout << "Something went wrong :(" << endl;
	}
	fclose(users);
}


void USERNAME::AddUser(USERNAME* user, int amount)
{
	for (int i = 0; i < amount; i++) {
		user[i].AskInformation();
	}
}
void USERNAME::AskInformation()
{
    if (index < MAX) {
        //full name 

        char buff[60];
        cout << "Name: ";
        cin >> buff;
       
        name = new char[strlen(buff) + 1];
        strcpy_s(name, strlen(buff) + 1, buff);

        cout << "Surname: ";
        cin >> buff;
        surname = new char[strlen(buff) + 1];
        strcpy_s(surname, strlen(buff) + 1, buff);


        //work phone
     
        while (!isCheckedPhone(buff)) {
            cout << "Work phone number (012) 123 1231: ";
            cin >> buff;
        }
      
        work_pfone = new char[strlen(buff) + 1];
        strcpy_s(work_pfone, strlen(buff) + 1, buff);

        
        //personal phone
       
        while (!isCheckedPhone(buff)) {
            cout << "Mobile phone number (012) 123 1231: ";
            cin >> buff;
        }
        personal_phone = new char[strlen(buff) + 1];
        strcpy_s(personal_phone, strlen(buff) + 1, buff);
        index++;
    }
    else {
        cout << "List is completely filled!" << endl;
    }
}
void USERNAME::AddPersonToFile(const char* filename, USERNAME* user)
{
    FILE* users;
    code = fopen_s(&users, filename, "w");
    if (users == 0)
    {
        cout << "Error opening file\n";
    }
    else
    {
        for (int i = 0; i < index; i++) {

            fprintf(users, "FIO: %s %s \n", user[i].name, user[i].surname);
            fprintf(users, "Work phone : %s \n", user[i].work_pfone);
            fprintf(users, "Mobile phone : %s \n\n", user[i].personal_phone);
        
        }
        cout << "Saved! " << endl;
        fclose(users);
        printf("User data loaded to file successfully!\n");
    }
}



bool USERNAME::isCheckedPhone(char* checkPhone)
{
    int size = 0;
    while (checkPhone[size] != '\0')
    {
        if (!isdigit(checkPhone[size]))
        {
            return false;
        }
        size++;
    }

    if (size == 10)
    {
        return true;
    }
    else {
        return false;
    }
}
void USERNAME::FindUserByFullName(USERNAME* user)
{
    if (index == 0)
    {
        cout << "List is empty!" << endl;
    }
    else {
        char buffName[20], buffMiddle[20];
        bool check = false;
        cout << "Enter FIO: ";
        cout << "Name: ";
        cin >> buffName;
        cout << "\tSurname: ";
        cin >> buffMiddle;

        cout << endl;

        for (int i = 0; i <index; i++) 
        {
            if ((strcmp(user[i].name, buffName) == 0) || (strcmp(user[i].surname, buffMiddle) == 0)) {
                check = true;
                user[i].GetUser(user, i);
            }
        }
        if (!check) 
        {
            cout << "Incorrect FIO" << endl;
        }
    }
}


void USERNAME::GetUser(USERNAME* user, int i)
{
    cout << "FIO: " << user[i].name << "\t" << user[i].surname << endl;
    cout << "Work number: " << user[i].work_pfone << endl;
    cout << "Mobile number: " << user[i].personal_phone << endl;
}

USERNAME* USERNAME::DeletePerson(USERNAME* user)
{
    char buff[20];
    int userIndex = -1;
    cout << "Enter user`s middleName: ";
    cin >> buff;


    for (int i = 0; i < index; i++) {
        if (strcmp(user[i].surname, buff) == 0)
        {
            userIndex = i;
            break;
        }
    }
    int new_size = 5;
    USERNAME* new_users = new USERNAME[new_size];
    int j = 0;
    for (int i = 0; i < index - 1; i++) {
        if (userIndex != -1) {
            //name
            new_users[j].name = new char[strlen(user[i].name) + 1];
            strcpy_s(new_users[j].name, strlen(buff) + 1, user[i].name);
            //middle name
            new_users[j].surname = new char[strlen(user[i].surname) + 1];
            strcpy_s(new_users[j].surname, strlen(buff) + 1, user[i].surname);
        

            //work phone
            new_users[j].work_pfone = new char[strlen(user[i].work_pfone) + 1];
            strcpy_s(new_users[j].work_pfone, strlen(buff) + 1, user[i].work_pfone);
            //personal phone
            new_users[j].personal_phone = new char[strlen(user[i].personal_phone) + 1];
            strcpy_s(new_users[j].personal_phone, strlen(buff) + 1, user[i].personal_phone);
            j++;
        }
    }
    delete[] user;
    cout << "Data deleted successfully" << endl;
    return new_users;
}
