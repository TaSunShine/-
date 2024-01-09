#include <iostream>
using namespace std;

class Card
{

	// 멤버는 private로 지정하고 public에서 get을 통해 부르는 형태.
private:
	char pattern;
	char denomination;

public:
	Card(char pattern, char getDenominaion); //Card클래스는 pattern과 Denomination을 속성으로 지니는 클래스.
	char getPattern();
    char getDenomination();

};



Card::Card(char pattern, char denomination) {
    this->pattern = pattern;
	this->denomination = denomination;
}



char Card::getPattern() { return pattern; }
char Card::getDenomination() { return denomination; } //생성자를 통한 private 멤버 호출





class Users{
	
	
	char name;
	int D;
	


};

// User 의도 : 컴퓨터나 유저나 같은 속성을 지니기에 클래스로 구현할 수 있을까 생각했는데
// 아직 다룰 능력이 안된다고 판단, 형태만 남아있다..