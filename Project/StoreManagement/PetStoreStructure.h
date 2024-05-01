#ifndef PET_STORE_STRUCTURE_H
#define PET_STORE_STRUCTURE_H

#include "PetStoreDisplay.h"
#include "PetClassStructure.h"
#include "StandardFunction.h"
//Push data from header<StandardFunction> to this->header
extern string ListOfCat[5];
extern float ListOfCatPrice[5];
extern string ListOfDog[5];
extern float ListOfDogPrice[5];
/// <summary>
///		Contain information to check condition in <Display Class>
/// </summary>
class Security {
public:
	//Condition to check player have enough budget to buy specific pets and quanity
	bool IsPurchaseable(float budget, float type, float quantity) {
		return budget >= (type * quantity) && budget >= 0;
	}
	//Condition to check player's budget should be >= the smallest amount in <PetCategory>
	bool AdoptCondition(vector<PetCategory> petList, float budget) {
		int min = INT_MAX;
		for (const auto& list : petList)
			if (min > list.petPrice) min = list.petPrice;
		return budget >= min;
	}
	//Check wrong input beside integer
#undef max
	int CheckWrongInput(string question, int& answer) {
		bool valid = false;

		do {
			cout << question; cin >> answer;

			if (cin.good()) {
				valid = true;
			}
			else {
				cout << "Invalid input; please re-enter." << endl;

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (!valid);

		return answer;
	}
};
/// <summary>
///		Contain important datas that prevent cheating in the game
/// </summary>
class Data {
protected:
	vector<PetCategory> petCategoryList;

	string nameOfUser;
	string nameOfUserStore;
	float budget;
public:
	//Push all data to make an organized pet list
	vector<PetCategory>& CreatePetList() {
		for (int i = 0; i < 5; i++) {
			this->petCategoryList.push_back(PetCategory("cat", ListOfCat[i], ListOfCatPrice[i]));
		}
		for (int i = 0; i < 5; i++) {
			this->petCategoryList.push_back(PetCategory("dog", ListOfDog[i], ListOfDogPrice[i]));
		}
		return petCategoryList;
	}

	void setUserName(string userName) {
		this->nameOfUser = userName;
	}

	string getNameOfUser() {
		return nameOfUser;
	}

	void setStoreName(string storeName) {
		this->nameOfUserStore = storeName;
	}

	string getNameOfUserStore() {
		return nameOfUserStore;
	}

	void setBudget(float initialBudget) {
		this->budget = initialBudget;
	}

	float getBudget() {
		return this->budget;
	}
};
/// <summary>
///		Display the game from all information provided
/// </summary>
class Display : public Security {
protected:
	vector<PetCategory> petCategoryList;
	vector<PetAdopt> petAdoptList;
	vector<PetAdopt> dataSave;

private:
	int petQuantity;
	float budget;
	int day;

	string ownerName;
	string storeName;

public:
	/// <summary>
	///		Push data: <Data> -> <Display>
	/// </summary>
	/// <param name="data"></param>
	Display(Data& data) {
		this->petCategoryList = data.CreatePetList();
		this->budget = data.getBudget();
		this->day = 1;

		this->ownerName = data.getNameOfUser();
		this->storeName = data.getNameOfUserStore();
	}
	/// <summary>
	///		Display pet purchase progress
	/// </summary>
	/// <param name="list"></param>
	void PurchaseProgress(vector<PetCategory> list) {
		int userAnswer = 0; int quantityAnswer = 0;
		string purchaseOption;

		while (purchaseOption != "N" && purchaseOption != "n" && AdoptCondition(list, this->budget)) {
			clearScreen();

			cout << "Your budget: " << this->budget << " --- ";
			cout << "Continue to adopt? (Y/N): "; cin >> purchaseOption;

			if (purchaseOption == "N" || purchaseOption == "n") break;
			else if (purchaseOption == "Y" || purchaseOption == "y") {
				cout << ">>>Choose your pet(s) by following list<<<" << endl;

				int index = 0;
				//Display pet category list
				for (const auto& pet : list) {
					index++;
					cout << index << ". " << "Type: " << pet.petType
						<< " --- " << "Gene: " << pet.petGene
						<< " --- " << "Price: " << pet.petPrice;
					cout << endl;
				} cout << endl;

				while (true)
				{
					do {
						CheckWrongInput("Your choice <index>: ", userAnswer);
						if (userAnswer < 0 || userAnswer > 9)
							cout << "Your input is not approriate" << endl;
					} while (userAnswer <= 0 || userAnswer > 9);

					userAnswer--;

					do {
						CheckWrongInput("Quantity: ", quantityAnswer);
						if (quantityAnswer < 0)
							cout << "Your input is not approriate" << endl;
					} while (quantityAnswer <= 0);

					if (!IsPurchaseable(this->budget, list[userAnswer].petPrice, quantityAnswer)) {
						if (quantityAnswer > 1) {
							cout << "Sorry, your budget is not enough for afford these little cute guys.";
							cout << endl << "Your budget: " << this->budget << endl;
						}

						else if (quantityAnswer == 1) {
							cout << "Sorry, your budget is not enough for afford this little sweetie.";
							cout << endl << "Your budget: " << this->budget << endl;
						}
						cout << endl;
					}

					if (IsPurchaseable(this->budget, list[userAnswer].petPrice, quantityAnswer)) break;
				}
				//Success purchase will be stored in two lists <PetAdopt>
				for (int i = 0; i < quantityAnswer; i++) {
					petAdoptList.push_back(PetAdopt((list[userAnswer])));
					dataSave = petAdoptList;
				}

				float purchaseMoney = list[userAnswer].petPrice * quantityAnswer;

				cout << "You successfully purchase " << quantityAnswer << " "
					<< list[userAnswer].petGene << " with " << purchaseMoney << "$";

				this->budget = this->budget - purchaseMoney;
				cout << endl << "Your budget: " << this->budget << "$";
			}
			//Check if player input wrong answer with warning publisehd
			else cout << "Your decision was misunderstood by computer."
				<< endl << "Please insert <Y/N> for far better performance!!!" << endl;
			Sleep(3000);
		}
	}
	/// <summary>
	///		Display each day to observe pet sold progress
	/// </summary>
	void OpenStore() {
		srand(time(NULL));
		//Random num of customer coming to the store
		int numOfCustomer = rand() % 20;
		vector<int> indexOfPetAdopt;
		int currentQuantity = petAdoptList.size();

		cout << "DAY " << day << " --- NUM OF CUSTOMER: " << numOfCustomer << endl;

		for (int i = 0; i < numOfCustomer; i++) {
			//Random possibility that there will be one customer will purchase a pet
			float randomPortion = (float)rand() / (float)RAND_MAX * 100;
			if (randomPortion < 5) {
				//Random to pick a pet from the store list
				int randomIndex; randomIndex = rand() % petAdoptList.size();
				for (const auto& index : indexOfPetAdopt) {
					while (randomIndex == index) {
						randomIndex = rand() % petAdoptList.size();
					}
				}
				//Push data from the chosen index to a seperate list
				indexOfPetAdopt.push_back(randomIndex);

				cout << endl << "Congratulation, 1 little cute "
					<< petAdoptList[randomIndex].getPetGene()
					<< " has a new home." << endl;

				cout << "Your reward: " << petAdoptList[randomIndex].getPetProfit();

				currentQuantity--;
				if (currentQuantity <= 0) break;
			}
		}
		pauseScreen(); EndOfDay(indexOfPetAdopt);
	}
	/// <summary>
	///		Summary a day with essential information
	/// </summary>
	/// <param name="usedIndex"></param>
	void EndOfDay(vector<int> usedIndex) {
		cout << ">>>ACHIEVEMENT DAY " << day << "<<<" << endl;
		cout << "List of pets that got owned by new owners:" << endl;

		float dayProfit = 0;
		float dayFee = 0;
		int newIndex = -1;

		for (int i = usedIndex.size() - 1; i >= 0; i--) {
			int index = usedIndex[i];
			//Check index from stored list not be overwhelmed
			if (index >= 0 && index < petAdoptList.size()) {
				newIndex++;
				cout << newIndex + 1 << ". " << "ID: " << petAdoptList[index].getPetId()
					<< " --- " << "Type: " << petAdoptList[index].getPetType()
					<< " --- " << "Gene: " << petAdoptList[index].getPetGene()
					<< " --- " << "Sold: " << petAdoptList[index].getPetProfit() << endl;
				//Count total information pet purchased before removing them out of list
				dayProfit += petAdoptList[index].getPetProfit() + petAdoptList[index].getPetPrice();
				dayFee += petAdoptList[index].getPetDailyCareFee();
				this->budget = this->budget + dayProfit - dayFee;
				//Erase pet that purchased out of the list
				petAdoptList.erase(petAdoptList.begin() + index);
			}
		}

		cout << "Your today's income: " << dayProfit << endl;
		cout << "Daily caring fee: " << dayFee << endl;
		cout << "Your current budget: " << this->budget << endl;

		pauseScreen();
		this->day++;
		Option();
	}
	/// <summary>
	///		Menu of the game
	/// </summary>
	void Option() {
		int userAnswer = -1;

		do {
			clearScreen();

			cout << ">>>SELECT YOUR NEXT STEP<<<" << endl;
			cout << "1. Check your store status" << endl << "2. Adopt more pet(s)" << endl
				<< "3. Continue to day " << this->day << endl << "4. Quit & Save" << endl;
			CheckWrongInput("Your answer: ", userAnswer);
		} while (userAnswer < 1 || userAnswer > 4);

		switch (userAnswer) {
		case 1: {
			clearScreen(); CheckStoreStatus();
			pauseScreen(); Option();
			break;
		}
		case 2: {
			clearScreen();
			if (!AdoptCondition(petCategoryList,this->budget)) {
				cout << "You don't have enough budget for any cuties :< So sorry" << endl;
				pauseScreen(); Option();
			}
			else {
				PurchaseProgress(petCategoryList);
				pauseScreen(); Option();
			}
			break;
		}
		case 3: {
			clearScreen();
			if (petAdoptList.size() == 0) {
				cout << "Your store is empty, come back when at least 1 pet adopted." << endl;
				pauseScreen(); Option();
			}
			else OpenStore();
			break;
		}
		case 4: {
			clearScreen();
			cout << "Thanks for playing, " << ownerName << ". "
				<< storeName << " Home will miss you alot ;.;" << endl;
			cout << "Hope you enjoy my further games in the future" << endl << endl;
			cout << "Developed by Thang Phan >< DemonDrac05" << endl;
			break;
		}
		}
	}
	/// <summary>
	///		Checking store list
	/// </summary>
	void CheckStoreStatus() {
		cout <<" --- OWNER: " << ownerName
			<< " --- STORE: " << storeName
			<< " --- BUDGET: " << budget << endl;

		if (petAdoptList.size() == 0) {
			cout << "You haven't adopted any pet(s) yet." << endl;
		}
		else for (size_t index = 0; index < petAdoptList.size(); index++) {
			cout << index + 1 << ". " << "ID: " << petAdoptList[index].getPetId()
				<< " --- " << "Type: " << petAdoptList[index].getPetType()
				<< " --- " << "Gene: " << petAdoptList[index].getPetGene()
				<< " --- " << "Price: " << petAdoptList[index].getPetPrice();
			cout << endl;
		}
	}
};
#endif PET_STORE_STRUCTURE_H
