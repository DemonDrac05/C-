#ifndef PET_STORE_DISPLAY_H
#define PET_STORE_DISPLAY_H

#include "PetClassStructure.h"
#include "PetStoreStructure.h"
#include "StandardFunction.h"
/// <summary>
///		Contain components and information of store created
///		Push the initial data to <Data Class>
/// </summary>
class PetStore {
protected:
	string nameOfUser;
	string nameOfUserStore;
	float storeBudget;
	Data data;

public:
	//Default account when player don't know what to do
	PetStore() {
		this->storeBudget = 500;
		this->nameOfUser = "Mr. Monday";
		this->nameOfUserStore = "PetWorld";
	}
	//Account registered depends on user
	PetStore(float initialBudget, string name, string storeName) {
		this->storeBudget = initialBudget;
		this->nameOfUser = name;
		this->nameOfUserStore = storeName;
	}
	//Account used by admin to test the game
	PetStore(PetStore& other) {
		this->storeBudget = other.storeBudget;
		this->nameOfUser = other.nameOfUser;
		this->nameOfUserStore = other.nameOfUserStore;
	}

	string& getUserName() {
		return nameOfUser;
	}

	string& getStoreName() {
		return nameOfUserStore;
	}

	float& getStoreBudget() {
		return storeBudget;
	}
	//Push data towards <Data Class>
	void GameOn() {
		data.setUserName(this->nameOfUser);
		data.setStoreName(this->nameOfUserStore);
		data.setBudget(this->storeBudget);

		Display display(data);
		display.Option();
	}
};
/// <summary>
///		Main event in main() <main.cpp>
/// </summary>
void gameOn() {
	string userName;
	string storeName;
	float storeBudget;

	cout << "Hello, welcome to Pet Store Simulator. May I have your name please?" << endl;
	cout << "<If you don't know what name you desire, you can press \"0\" to play>" << endl;
	cout << "Your name: ";
	cin >> userName;
	//Trial account for unregistered player
	if (userName == "0") {
		PetStore pet;

		userName = pet.getUserName();
		storeName = pet.getStoreName();
		storeBudget = pet.getStoreBudget();
	}
	//Secret account used by admin
	else if (userName == "admin") {
		float adminBudget = 9999;
		PetStore pet(adminBudget, "Admin", "AdminWorld");
		PetStore adminPetStore(pet);

		userName = adminPetStore.getUserName();
		storeName = adminPetStore.getStoreName();
		storeBudget = adminPetStore.getStoreBudget();
	}
	//Player individually creates a store with limit budget
	else {
		cout << "Your store name: ";
		cin >> storeName;
		do {
			cout << "Your initial budget (500$ - 1000$): ";
			cin >> storeBudget;
			if (storeBudget < 500 || storeBudget > 1000) {
				cout << "Please input a number between 500 and 1000!!!" << endl;
			}
		} while (storeBudget < 500 || storeBudget > 1000);
	}
	//Push data back to <PetStore>
	PetStore userPetStore(storeBudget, userName, storeName);

	clearScreen();

	userPetStore.GameOn();
}
#endif PET_STORE_DISPLAY_H
