#pragma once


class USERNAME
{
private:
	char* name;
	char* surname;
	char* work_pfone;
	char* personal_phone;
	int index;

public:
	
	USERNAME();
	~USERNAME();

    void ShowUserData(const char* filename, USERNAME* user);

    void AddPersonToFile(const char* filename, USERNAME* user);
	void AskInformation();
	void AddUser(USERNAME* user, int amount);

	bool isCheckedPhone(char* checkPhone);
	
	
	
	void FindUserByFullName(USERNAME* user);
	void GetUser(USERNAME* user, int i);

	USERNAME* DeletePerson(USERNAME* user);


};

