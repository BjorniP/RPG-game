#pragma once
class AttributeComponent
{
public:

	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;
    
	//Attributes
	int strength;
	int vitality;
	int agility;
	int dexterity;
	int intelligence;
	int MaximumSkill;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	//Cons/Desctructors
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	const bool isDead() const;
	const bool VitalityMax();
	const bool AgilityMax();
	const bool IntelligenceMax();
	const bool DexterityMax();
	const bool StrengthMax();
	std::string debugPrint() const;
	void updateStats(const bool reset);
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseExp(const int exp);
	void gainExp(const int exp);
	void removeAttributePoints();
	void updatelevelUp();
	void update();
};

