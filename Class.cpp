#include "Class.h"
#include <vector>
#include <cstdlib>
#include <ctime>
// include는 헤더에 지정했으면 여기는 안 해도 된다.
// 그래서 iostream만은 헤더에서도 사용하므로 헤더파일에 놔두고 나머지는 소스파일에서 불러보았다.

// 16번과 17번은 주석 모두 달라는 의도 : 코드를 이해했는가, 
// 컨닝만으로 제출한 것은 아닌가 확인하려는 의도로 생각해서
// 기본적인 부분들은 주석 안달았습니다!!!!!!!!!!!!!


static char  cardDenomination[] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
static char  cardPattern[] = { 'S','H','C','D' };
// 위의 2개는 각각 문양(블랙잭에선 의미가 없고 단순히 카드 구분하는 용도인듯), 숫자를 의미하며 서로다른 문양과 숫자가 모여
// 우리가 아는 트럼프카드가 된다.


vector<Card> allCards, dealCards, userCards; // 전체카드와 딜러의카드,유저의 카드는 모두 연관되어있기에 전역변수로써 컨트롤한다.

int dealWin = 0, userWin = 0; //초기화는 승리횟수를 초기화.

// 카드 초기화
void initSetting();
// 카드 받기
void receiveCard(char);
//승률
int Winrate(int, int);
// HIT여부 확인
bool hit();
// 점수 계산
int computeScore(vector<Card>);
// 승자여부 결정
void decideWinner();
// 게임 다시하기 여부 확인
bool gameAgain();
// 규칙 설명
void Rule();

void initSetting() { //초기화는 벡터를 통해서 진행되며 모든 카드를 allCards라는 벡터속으로 넣어버리는 것이 초기화를 의미한다.
	for (int i = 0; i < sizeof(cardPattern) / sizeof(char); i++) {
		for (int j = 0; j < sizeof(cardDenomination) / sizeof(char); j++) {
			allCards.push_back(Card(cardPattern[i], cardDenomination[j]));
		}
	}
}
void Rule() {
	//단순한 룰 설명, 필요할 경우 r를 통해 호출되므로 메소드로 빼버렸다.
	cout << "딜러와의 블랙잭을 시작합니다. 규칙은 다음과 같습니다." << endl << endl <<
		"1. 가진 카드의 합이 22이상이 되면 패배합니다." << endl <<
		"2. S는 스페이드, H는 하트, C는 클로버, D는 다이아몬드입니다." << endl <<
		"3. T,J,K,Q는 모두 10의 값을 갖습니다." << endl <<
		"4. A는 일반적으론 값이 1 이지만 자신이 가진 카드의 합이 11보다 클 경우는 11의 값을 갖습니다." << endl <<
		"5. Hit를 그만둘 때 딜러와 점수가 적거나 같으면 패배합니다." << endl <<
		"   해당 설명을 다시 보고 싶으시면 R을 입력하시면 됩니다. " 
		<< endl << endl;

}


// 카드 받기
void receiveCard(char du) {
	int num = rand() % allCards.size();
	// 임의카드 한 장 선택
	Card card = (Card)allCards[num];
	// 선택된 카드 삭제
	allCards.erase(allCards.begin() + num);
	// 딜러 또는 유저 Card리스트에 추가
	if (du == 'd')		dealCards.push_back(card);
	else if (du == 'u')		userCards.push_back(card);
}

// hit 여부
bool hit() {
	// 좀 더 특별하게 만들었다.
    // 문양과 숫자를 보고 점수구분이 어렵기에 
	// 아예 점수를 이 때 알려주고, 필요할 경우 룰을 다시 호출해서 규칙을 읽을 수 있게 만들었다.
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
// 승률 계산
int Winrate(int  user, int deal) {
	// 단순히 승률만을 계산하면 되므로 그냥 메소드로 빼버렸다.
	int Result = 0;
	if (user == 0) {
		return 0;
	}
	else {
		Result = (userWin * 100) / (userWin + dealWin);
		return Result;
	}
}
// 점수계산
int computeScore(vector<Card> cards) {
	int score = 0; // name은 Denomination numAce는 A만을 대상으로 하는 변수
	int numAce = 0;
	for (int i = 0; i < cards.size(); i++) {
		// cards.size라함은 크기를 의미하므로 보유중인 카드가 1개, 2개여도 1개 2개만큼을 계산하는 형태를 띔.
		// 그렇게 Denimination은 숫자 그대로 더하고 (T이후값은 모두 10) 특별한 A만은
		// 본인을 제외한 수들이 11이상일 경우는 11, 그렇지 않을 경우는 1로 취급하여 계산.

		Card card = (Card)cards[i];
		char name = card.getDenomination();
		if (name == 'A') 
			numAce++;
		else if (name == 'T' || name == 'J' || name == 'Q' || name == 'K')
			score += 10;
		else score += name - '0';
	}
	// 점수계산
	for (int i = 0; i < numAce; i++) {
		if (score < 11) score += 11;
		else score += 1;
	}

	return score;
}

// 승자 판단
void decideWinner() {

	int user = computeScore(userCards);
	int deal = computeScore(dealCards);
	//해당 메소드에서는 compiteScore를 통해 도출된 값을 user,deal 지역변수로써 판단합니다.


	if ( user > 21 || (deal <= 21 && user <= deal)) {
        // 점수가 21점을 넘어가거나, 유저가 딜러보다 같거나 적은경우 패배처리하는 식
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

// 한 게임 더 확인
bool gameAgain() {
	char again = 'N';
	cout << "GAME AGAIN ? ( Y / N ) : ";
	cin >> again;
	cout << endl;
	if (again == 'Y' || again == 'y') {
		// 모든 카드를 초기화.
		allCards.clear();
		dealCards.clear();
		userCards.clear();
		return true;
	}
	else return false;
}

int main() {
	srand(time(NULL)); // 실행시 랜덤 시드값 설정하는 느낌
	
	Rule();

	do {
		//vector<Card> allCards;
		initSetting();
		// dealer 는 두 장 받기
		receiveCard('d');
		receiveCard('d');
		receiveCard('u');

		// user가 hit 여부에 n을 입력할 때 까지
		do {
			if (userCards.size() >= 4) {
				cout << "카드를 5개 이상 보유하여 자동으로 패배합니다." << endl << endl;
				dealWin++;
				initSetting(); //패배 처리 후 초기화
				break;
				
			}
			
			receiveCard('u');
			
			if (computeScore(userCards) > 21) {
				cout << "22점 이상이 되었습니다. 자동으로 패배합니다." << endl << endl;
				dealWin++;
				initSetting(); //패배 처리 후 초기화
				break;
			}

			cout << " 당신의 카드 : ";
			for (auto iter : userCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
			cout << endl;
			
			
			// dealer의 카드 값이 17미만이면 dealer 카드 받기
			if (computeScore(dealCards) < 17) receiveCard('d');
		} while (hit()); // hit()함수에서 false를 리턴할 때까지 반복

		// 승자 판단
		decideWinner();

		cout << "딜러의 카드 : ";
		for (auto iter : dealCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
		cout << endl;
		cout << "당신의 카드 : ";
		for (auto iter : userCards) cout << iter.getPattern() << iter.getDenomination() << "  ";
		cout << endl << endl;
		cout << "현재까지 당신의 승리횟수 : " << userWin <<
			"\n 딜러의 승리 횟수 : " << dealWin <<
			"\n" << "현재 당신의 승률 : " << Winrate(userWin,dealWin) << "%" <<
			"\n" ;
		// 승자 판단 후, 딜러와 자신의 카드를 보여주면서
		// 현재까지 승리횟수를 출력하고 딜러와의 승률을 보여주어보았다.
	
 	
	} while (gameAgain());
}
