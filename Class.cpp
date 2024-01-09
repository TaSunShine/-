#include "Class.h"
#include <vector>
#include <cstdlib>
#include <ctime>
// include�� ����� ���������� ����� �� �ص� �ȴ�.
// �׷��� iostream���� ��������� ����ϹǷ� ������Ͽ� ���ΰ� �������� �ҽ����Ͽ��� �ҷ����Ҵ�.

// 16���� 17���� �ּ� ��� �޶�� �ǵ� : �ڵ带 �����ߴ°�, 
// ���׸����� ������ ���� �ƴѰ� Ȯ���Ϸ��� �ǵ��� �����ؼ�
// �⺻���� �κе��� �ּ� �ȴ޾ҽ��ϴ�!!!!!!!!!!!!!


static char  cardDenomination[] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
static char  cardPattern[] = { 'S','H','C','D' };
// ���� 2���� ���� ����(���迡�� �ǹ̰� ���� �ܼ��� ī�� �����ϴ� �뵵�ε�), ���ڸ� �ǹ��ϸ� ���δٸ� ����� ���ڰ� ��
// �츮�� �ƴ� Ʈ����ī�尡 �ȴ�.


vector<Card> allCards, dealCards, userCards; // ��üī��� ������ī��,������ ī��� ��� �����Ǿ��ֱ⿡ ���������ν� ��Ʈ���Ѵ�.

int dealWin = 0, userWin = 0; //�ʱ�ȭ�� �¸�Ƚ���� �ʱ�ȭ.

// ī�� �ʱ�ȭ
void initSetting();
// ī�� �ޱ�
void receiveCard(char);
//�·�
int Winrate(int, int);
// HIT���� Ȯ��
bool hit();
// ���� ���
int computeScore(vector<Card>);
// ���ڿ��� ����
void decideWinner();
// ���� �ٽ��ϱ� ���� Ȯ��
bool gameAgain();
// ��Ģ ����
void Rule();

void initSetting() { //�ʱ�ȭ�� ���͸� ���ؼ� ����Ǹ� ��� ī�带 allCards��� ���ͼ����� �־������ ���� �ʱ�ȭ�� �ǹ��Ѵ�.
	for (int i = 0; i < sizeof(cardPattern) / sizeof(char); i++) {
		for (int j = 0; j < sizeof(cardDenomination) / sizeof(char); j++) {
			allCards.push_back(Card(cardPattern[i], cardDenomination[j]));
		}
	}
}
void Rule() {
	//�ܼ��� �� ����, �ʿ��� ��� r�� ���� ȣ��ǹǷ� �޼ҵ�� �����ȴ�.
	cout << "�������� ������ �����մϴ�. ��Ģ�� ������ �����ϴ�." << endl << endl <<
		"1. ���� ī���� ���� 22�̻��� �Ǹ� �й��մϴ�." << endl <<
		"2. S�� �����̵�, H�� ��Ʈ, C�� Ŭ�ι�, D�� ���̾Ƹ���Դϴ�." << endl <<
		"3. T,J,K,Q�� ��� 10�� ���� �����ϴ�." << endl <<
		"4. A�� �Ϲ������� ���� 1 ������ �ڽ��� ���� ī���� ���� 11���� Ŭ ���� 11�� ���� �����ϴ�." << endl <<
		"5. Hit�� �׸��� �� ������ ������ ���ų� ������ �й��մϴ�." << endl <<
		"   �ش� ������ �ٽ� ���� �����ø� R�� �Է��Ͻø� �˴ϴ�. " 
		<< endl << endl;

}


// ī�� �ޱ�
void receiveCard(char du) {
	int num = rand() % allCards.size();
	// ����ī�� �� �� ����
	Card card = (Card)allCards[num];
	// ���õ� ī�� ����
	allCards.erase(allCards.begin() + num);
	// ���� �Ǵ� ���� Card����Ʈ�� �߰�
	if (du == 'd')		dealCards.push_back(card);
	else if (du == 'u')		userCards.push_back(card);
}

// hit ����
bool hit() {
	// �� �� Ư���ϰ� �������.
    // ����� ���ڸ� ���� ���������� ��Ʊ⿡ 
	// �ƿ� ������ �� �� �˷��ְ�, �ʿ��� ��� ���� �ٽ� ȣ���ؼ� ��Ģ�� ���� �� �ְ� �������.
	char input = 'N';

	cout << " Now Cards Score : " << computeScore(userCards) << "\n";
	cout << "Hit ? ( Y/ N ) : ";
	cin >> input;
	cout << endl;

	
	if (input == 'Y' || input == 'y') return true;
	else if (input == 'r' || input == 'R') {
		Rule();
		return hit();
	}
		
		else return false;
}
// �·� ���
int Winrate(int  user, int deal) {
	// �ܼ��� �·����� ����ϸ� �ǹǷ� �׳� �޼ҵ�� �����ȴ�.
	int Result = 0;
	if (user == 0) {
		return 0;
	}
	else {
		Result = (userWin * 100) / (userWin + dealWin);
		return Result;
	}
}
// �������
int computeScore(vector<Card> cards) {
	int score = 0; // name�� Denomination numAce�� A���� ������� �ϴ� ����
	int numAce = 0;
	for (int i = 0; i < cards.size(); i++) {
		// cards.size������ ũ�⸦ �ǹ��ϹǷ� �������� ī�尡 1��, 2������ 1�� 2����ŭ�� ����ϴ� ���¸� ��.
		// �׷��� Denimination�� ���� �״�� ���ϰ� (T���İ��� ��� 10) Ư���� A����
		// ������ ������ ������ 11�̻��� ���� 11, �׷��� ���� ���� 1�� ����Ͽ� ���.

		Card card = (Card)cards[i];
		char name = card.getDenomination();
		if (name == 'A') 
			numAce++;
		else if (name == 'T' || name == 'J' || name == 'Q' || name == 'K')
			score += 10;
		else score += name - '0';
	}
	// �������
	for (int i = 0; i < numAce; i++) {
		if (score < 11) score += 11;
		else score += 1;
	}

	return score;
}

// ���� �Ǵ�
void decideWinner() {

	int user = computeScore(userCards);
	int deal = computeScore(dealCards);
	//�ش� �޼ҵ忡���� compiteScore�� ���� ����� ���� user,deal ���������ν� �Ǵ��մϴ�.


	if ( user > 21 || (deal <= 21 && user <= deal)) {
        // ������ 21���� �Ѿ�ų�, ������ �������� ���ų� ������� �й�ó���ϴ� ��
		dealWin++;
		cout << "DEALER WIN!" << endl;
	}

	else {
		userWin++;
		cout << "USER WIN!" << endl;
	}
	cout << "DEALER Score: " << deal << endl;
	cout << "USER Score: " << user << endl;
}

// �� ���� �� Ȯ��
bool gameAgain() {
	char again = 'N';
	cout << "GAME AGAIN ? ( Y / N ) : ";
	cin >> again;
	cout << endl;
	if (again == 'Y' || again == 'y') {
		// ��� ī�带 �ʱ�ȭ.
		allCards.clear();
		dealCards.clear();
		userCards.clear();
		return true;
	}
	else return false;
}

int main() {
	srand(time(NULL)); // ����� ���� �õ尪 �����ϴ� ����
	
	Rule();

	do {
		//vector<Card> allCards;
		initSetting();
		// dealer �� �� �� �ޱ�
		receiveCard('d');
		receiveCard('d');
		receiveCard('u');

		// user�� hit ���ο� n�� �Է��� �� ����
		do {
			if (userCards.size() >= 4) {
				cout << "ī�带 5�� �̻� �����Ͽ� �ڵ����� �й��մϴ�." << endl << endl;
				dealWin++;
				initSetting(); //�й� ó�� �� �ʱ�ȭ
				break;
				
			}
			
			receiveCard('u');
			
			if (computeScore(userCards) > 21) {
				cout << "22�� �̻��� �Ǿ����ϴ�. �ڵ����� �й��մϴ�." << endl << endl;
				dealWin++;
				initSetting(); //�й� ó�� �� �ʱ�ȭ
				break;
			}

			cout << " ����� ī�� : ";
			for (auto iter : userCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
			cout << endl;
			
			
			// dealer�� ī�� ���� 17�̸��̸� dealer ī�� �ޱ�
			if (computeScore(dealCards) < 17) receiveCard('d');
		} while (hit()); // hit()�Լ����� false�� ������ ������ �ݺ�

		// ���� �Ǵ�
		decideWinner();

		cout << "������ ī�� : ";
		for (auto iter : dealCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
		cout << endl;
		cout << "����� ī�� : ";
		for (auto iter : userCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
		cout << endl << endl;
		cout << "������� ����� �¸�Ƚ�� : " << userWin <<
			"\n ������ �¸� Ƚ�� : " << dealWin <<
			"\n" << "���� ����� �·� : " << Winrate(userWin,dealWin) << "%" <<
			"\n" ;
		// ���� �Ǵ� ��, ������ �ڽ��� ī�带 �����ָ鼭
		// ������� �¸�Ƚ���� ����ϰ� �������� �·��� �����־�Ҵ�.
	
 	
	} while (gameAgain());
}
