#include <iostream>
using namespace std;

class Card
{

	// ����� private�� �����ϰ� public���� get�� ���� �θ��� ����.
private:
	char pattern;
	char denomination;

public:
	Card(char pattern, char getDenominaion); //CardŬ������ pattern�� Denomination�� �Ӽ����� ���ϴ� Ŭ����.
	char getPattern();
    char getDenomination();

};



Card::Card(char pattern, char denomination) {
    this->pattern = pattern;
	this->denomination = denomination;
}



char Card::getPattern() { return pattern; }
char Card::getDenomination() { return denomination; } //�����ڸ� ���� private ��� ȣ��





class Users{
	
	
	char name;
	int D;
	


};

// User �ǵ� : ��ǻ�ͳ� ������ ���� �Ӽ��� ���ϱ⿡ Ŭ������ ������ �� ������ �����ߴµ�
// ���� �ٷ� �ɷ��� �ȵȴٰ� �Ǵ�, ���¸� �����ִ�..