#ifndef PET_CLASS_STRUCTURE_H
#define PET_CLASS_STRUCTURE_H

#include "StandardFunction.h"
/// <summary>
///		Contain information about different types of pet
/// </summary>
class PetCategory {
public:
	string petType;
	string petGene;
	float petPrice;

	PetCategory(string type, string name, float price) {
		this->petType = type;
		this->petGene = name;
		this->petPrice = price;
	}
};
/// <summary>
///		Contain information of each pet that adopted
/// </summary>
class PetAdopt {
protected:
	int petId;
private:
	string petType;
	string petGene;
	float petPrice;
	float petProfit;
	float petDailyCareFee;
public:
	PetAdopt(PetCategory category) {
		petType = category.petType;
		petGene = category.petGene;
		petPrice = category.petPrice;

		srand(time(NULL));

		this->petId = GeneratePetId();
		this->petProfit = GeneratePetProfit();
		this->petDailyCareFee = GenerateDailyFee();
	}

	string getPetType() {
		return petType;
	}

	string getPetGene() {
		return petGene;
	}

	float getPetPrice() {
		return petPrice;
	}

	float getPetProfit() {
		return petProfit;
	}

	float getPetDailyCareFee() {
		return petDailyCareFee;
	}

	int getPetId() {
		return petId;
	}

	unsigned int GeneratePetId() {
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<unsigned int> dis(0x0, 0xFFFF);

		return dis(gen);
	}

	float GeneratePetProfit() {
		float extraLuck = ((float)rand()/RAND_MAX) * 100;

		float profit; float tip;
		// Random based on probabilities
		if (extraLuck < 11) {
			profit = (this->petPrice * 0.35) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.5);
			tip = profit * 0.1;
		}
		else if (extraLuck < 21) {
			profit = (this->petPrice * 0.25) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.3);
			tip = (profit * 0.05) + ((float)rand() / RAND_MAX) * (profit * 0.1);
		}
		else if (extraLuck < 31) {
			profit = (this->petPrice * 0.15) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.2);
			tip = (profit * 0.02) + ((float)rand() / RAND_MAX) * (profit * 0.04);
		}
		else {
			profit = (this->petPrice * 0.05) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.1);
			tip = profit * 0.01;
		}

		return profit + tip;
	}

	float GenerateDailyFee() {
		if (this->petType == "cat")
			return (this->petPrice * 0.005) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.01);
		else return (this->petPrice * 0.02) + ((float)rand() / RAND_MAX) * (this->petPrice * 0.03);
	}
};
#endif PET_CLASS_STRUCTURE_H
