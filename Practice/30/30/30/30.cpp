#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <Windows.h>

using std::vector;
using std::ostream;
using std::string;

enum IT {
	COIN, RUNE, WEAPON, ARMOR
};

enum ET {
	FIRE, WATER, EARTH, AIR
};

union CT {
	struct {
		int		count;
	} Coin;
	struct {
		int		level;
		enum ET element;
	} Rune;
	struct {
		int		damage;
		int		critical;
		int		durability;
	} Weapon;
	struct {
		int		guard;
		int		durability;
	} Armor;
};

struct Item {
	enum IT	ItemType;
	union CT Item;
};

typedef vector<Item> LootBox;

LootBox& operator<<(LootBox& lb, Item x) {
	lb.push_back(x);
	return lb;
}

class Randomizer {
private:
	vector<double> probdb;
public:
	LootBox db;
	void add(Item x, double prob);
	Item get(int id);
	Item getrnd();
} random;

void Randomizer::add(Item x, double prob) {
	db << x;
	if (probdb.size() <= 0) {
		probdb.push_back(prob);
	}
	else {
		probdb.push_back(prob + probdb[probdb.size() - 1]);
	}
}

Item Randomizer::get(int id) {
	return db.at(id);
}

Item Randomizer::getrnd() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 100.0);
	double rnd = dist(mt);
	for (int i = 0; i < db.size(); i++) {
		if (rnd <= probdb[i])
			return this->get(i);
	}
	return {};
}

Item operator++(Item x) {
	return random.getrnd();
}

ostream& operator<<(ostream& os, Item x) {
	switch (x.ItemType) {
	case COIN:
		os << x.Item.Coin.count << " gold";
		break;
	case RUNE:
#define get_enum_name(id) vector<string>{"fire", "water", "earth", "air"}[int(id)]
		os << "Rune of " << get_enum_name(x.Item.Rune.element) << " " << x.Item.Rune.level << " lvl";
		break;
	case WEAPON:
		if ((x.Item.Weapon.damage == 100) && (x.Item.Weapon.critical == 0))
			os << "God Killer";
		if ((x.Item.Weapon.damage == 75) && (x.Item.Weapon.critical == 50))
			os << "Demon Slayer";
		break;
	case ARMOR:
		os << "Bronezhiletka";
		break;
	}
	return os;
}

ostream& operator<<(ostream& os, LootBox x) {
	for (int i = 0; i < x.size(); i++) {
		os << x[i] << std::endl;
	}
	return os;
}

void lootBoxInit() {
	/* Coins */
	random.add({ COIN, 1000 }, 50);
	/* Runes */
	for (int i = 0; i <= 11; i++) {
		Item x;
		x.ItemType = RUNE;
		x.Item.Rune.element = ET(i % 4);
		x.Item.Rune.level = (i > 3) ? 1 : 5;
		double k = vector<double>{ 6, 13, 7, 14, 0.6, 1.3, 0.7, 1.4, 0.06, 0.13, 0.07, 0.14 }[i];
		random.add(x, k);
	}
	/* Weapons */
	for (int i = 0; i <= 1; i++) {
		Item w;
		w.ItemType = WEAPON;
		w.Item.Weapon.damage = i == 0 ? 100 : 75;
		w.Item.Weapon.critical = i == 0 ? 0 : 50;
		w.Item.Weapon.durability = 100;
		random.add(w, 1.4);
	}
	/* Armor */
	{
		Item a;
		a.ItemType = ARMOR;
		a.Item.Armor.guard = 50;
		a.Item.Armor.durability = 100;
		random.add(a, 2.8);
	}
}

LootBox generateLootBox() {
	LootBox lb;
	for (int i = 0; i <= 2; i++) {
		Item x = {};
		lb << ++x;
	}
	return lb;
}

bool isUserAgree() {
	while (1) {
		string s;
		std::cout << "Открыть лутбокс? Yes/No\n>";
		std::cin >> s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if ((s == "y") || (s == "yes")) {
			return 1;
		}
		if ((s == "n") || (s == "no")) {
			return 0;
		}
		std::cout << std::endl;
		continue;
	}
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	lootBoxInit();
	while (isUserAgree()) {
		std::cout << generateLootBox();
	}
}