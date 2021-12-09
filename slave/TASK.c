#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"
#include "KEY.h"

static uint8_t* player1[10][5] = {
	{"Activate the Tilayhia!", "Stabilize the Zoebeet!", "Toggle the Awepebiypi!", "Propel the Oxeeh!", "Flip the Qooxey!"},
	{"Initialize the Elaumaa!", "Push the Ivomoyye!", "Toggle the Uluvuavyi!", "Trigger the Yvoqudiyak!", "Toggle the Izykiihy!"},
	{"Press the Eliziyq!", "Initialize the Woodiyj!", "Press the Zosesuy!", "Initialize the Egore!", "Turn on the Asilauxy!"},
	{"Push the Odidacy!", "Propel the Vutiyikuiy!", "Push the Eruama!", "Flip the Acynekua!", "Toggle the Aqoik!"},
	{"Push the Duura!", "Stabilize the Nupeyywi!", "Activate the Ejyylugais!", "Push the Akooreja!", "Mobilize the Yqatif!"},
	{"Toggle the Cuefiqoufo!", "Press the Pyfiayubal!", "Toggle the Yvyju!", "Push the Ofanupo!", "Energize the Ojiegyja!"},
	{"Trigger the Edodoyy!", "Mobilize the Woygey!", "Activate the Ycytefoge!", "Start the Haxaot!", "Press the Capas!"},
	{"Energize the Igywuakex!", "Turn on the Ubeihe!", "Turn on the Amuty!", "Mobilize the Ojeelyisu!", "Toggle the Fegac!"},
	{"Compress the Ofiedeici!", "Compress the Yimuapie!", "Activate the Hyeqiu!", "Toggle the Wyuciarieh!", "Initialize the Ugiikuiq!"},
	{"Propel the Raisazip!", "Turn on the Teysasye!", "Turn on the Yecizaucof!", "Push the Ygyrypapea!", "Compress the Ipecuu!"}
};
static uint8_t* player2[10][16] = {
	{"Mobilize the Adaohiqyca!", "Activate the Laybiqe!", "Turn on the Wohit!", "Energize the Uhacyl!", "Stabilize the Huleluaho!", "Initialize the Nupeyywi!", "Energize the Moosuyypa!", "Toggle the Lotietinob!", "Stabilize the Ycahiw!", "Start the Ovoaz!", "Trigger the Xefet!", "Stabilize the Oduajij!", "Flip the Saeyypeeh!", "Start the Fiyeraa!", "Initialize the Wydyvoi!", "Press the Ilyep!"},
	{"Initialize the Negyewow!", "Activate the Ykaetuy!", "Propel the Ahiypa!", "Trigger the Asioquk!", "Press the Ahejiajyef!", "Flip the Idijym!", "Compress the Dilufy!", "Propel the Yjysuywafy!", "Compress the Sydopeosou!", "Initialize the Wuelol!", "Start the Ifeaguaz!", "Compress the Iloehed!", "Propel the Duryiteo!", "Energize the Hydaipuo!", "Trigger the Udipu!", "Propel the Omeumiday!"},
	{"Trigger the Izaobu!", "Compress the Nuafon!", "Trigger the Uyujo!", "Energize the Uhacyl!", "Stabilize the Yreehoyki!", "Compress the Heyxagije!", "Compress the Zyogaticu!", "Flip the Pexoynyda!", "Propel the Odiqiweky!", "Trigger the Yxiyhuaz!", "Mobilize the Deohypy!", "Toggle the Uzufuroan!", "Press the Areyvaur!", "Toggle the Boaqauz!", "Energize the Yuzapy!", "Compress the Eforuema!"},
	{"Propel the Etamoh!", "Stabilize the Zavuzayre!", "Press the Asioquk!", "Toggle the Ykosax!", "Press the Quibeacay!", "Initialize the Uyixan!", "Toggle the Ohyiqaaqa!", "Toggle the Owayxumaqo!", "Mobilize the Adyota!", "Trigger the Pezyuq!", "Press the Suyloruak!", "Press the Demei!", "Compress the Gireloy!", "Compress the Ageayik!", "Initialize the Obucouh!", "Turn on the Enaihoije!"},
	{"Compress the Zoukeesaz!", "Stabilize the Aryugifyu!", "Push the Soami!", "Propel the Uguwoi!", "Mobilize the Obyji!", "Stabilize the Unoge!", "Compress the Ipogacaba!", "Flip the Qouheunuis!", "Start the Gaefee!", "Initialize the Atuyseucik!", "Trigger the Ezipa!", "Stabilize the Qiyhy!", "Flip the Utoad!", "Press the Ovaaf!", "Turn on the Umouhum!", "Push the Fyafeapyi!"},
	{"Toggle the Tyujidorel!", "Compress the Obiyorioly!", "Stabilize the Ovuvy!", "Push the Ofawev!", "Initialize the Wohit!", "Compress the Byihonoh!", "Trigger the Uxuyureod!", "Initialize the Ukoitual!", "Activate the Yufowo!", "Toggle the Veoseahui!", "Mobilize the Ypoudeyki!", "Trigger the Yeniywoaw!", "Initialize the Puojovea!", "Flip the Ziexy!", "Propel the Gigadiif!", "Energize the Taeyadukaj!"},
	{"Press the Taizecyzay!", "Compress the Famolym!", "Trigger the Eheefosep!", "Trigger the Ukuzamiok!", "Push the Oxomahec!", "Initialize the Baeyeyubaw!", "Compress the Agoxaze!", "Stabilize the Ubeihe!", "Stabilize the Ipiifiuje!", "Push the Utoytakola!", "Mobilize the Ifiogeboz!", "Compress the Sezagyykiy!", "Start the Yroypuakoo!", "Turn on the Quibeacay!", "Trigger the Dyudah!", "Toggle the Fekuseb!"},
	{"Start the Toinajenuj!", "Energize the Upeno!", "Start the Hyzyomopy!", "Activate the Viojegen!", "Activate the Tucuyquhi!", "Flip the Nupeyywi!", "Initialize the Isaeqaonyo!", "Mobilize the Ezooky!", "Compress the Jyziaqoyuk!", "Turn on the Tioye!", "Propel the Yevao!", "Trigger the Opiet!", "Activate the Oxeeh!", "Flip the Vomogex!", "Propel the Pyocomug!", "Initialize the Wemexuwio!"},
	{"Mobilize the Ahoyyupio!", "Flip the Yzounin!", "Turn on the Qaomiuvux!", "Press the Pabeycuge!", "Activate the Faulo!", "Turn on the Cazufi!", "Initialize the Lytaybo!", "Propel the Ewule!", "Mobilize the Luduigawy!", "Propel the Caveacaepe!", "Flip the Rayxea!", "Mobilize the Ycivuyyyz!", "Push the Ryoqeikuc!", "Start the Zayqobiali!", "Initialize the Adymoseum!", "Trigger the Wuquo!"},
	{"Trigger the Bougeo!", "Start the Yezuom!", "Mobilize the Unoatu!", "Stabilize the Ehomawag!", "Toggle the Yyyogys!", "Stabilize the Bevaa!", "Start the Myoryuly!", "Start the Uhinowyawa!", "Start the Iruroj!", "Energize the Yqoywedoa!", "Activate the Inoyvoiy!", "Mobilize the Evahauniy!", "Push the Opicuiji!", "Trigger the Sezagyykiy!", "Stabilize the Ehiedenaow!", "Start the Xoulyzaty!"}
};


/*
// Player 1 has the buttons
// Each button is pulled up with a 2.2k resistor
static uint8_t* player1[5] = { 
	"Press the red button", // 0
	"Press the blue button", // 1
	"Press the green button", // 2
	"Press the yellow button", // 3
	"Press the black button" // 4
	/*"Flip the switch", // 5
	"Press the ", // 6
	"Press the ", // 7
	"Press the ", // 8
	"Press the ", // 9
	"Press the ", // 10
	"Press the ", // 11
	"Press the ", // 12
	"Press the ", // 13 
	"Press the ", // 14
	"Press the "  // 15
};

// Player 2 has the keypad
static uint8_t* player2[16] = { 
	"Press the 0 key", // 0
	"Press the 1 key", // 1
	"Press the 2 key", // 2
	"Press the 3 key", // 3
	"Press the 4 key", // 4
	"Press the 5 key", // 5
	"Press the 6 key", // 6
	"Press the 7 key", // 7
	"Press the 8 key", // 8
	"Press the 9 key", // 9
	"Press the A key", // 10
	"Press the B key", // 11
	"Press the C key", // 12
	"Press the D key", // 13 
	"Press the # key", // 14
	"Press the * key"  // 15
};
*/

static uint8_t player1_com = 0;
static uint8_t player2_com = 0;
uint8_t gm = 0;

void set_mode(uint8_t mode) {
	gm = mode;
}

// Task Slave Function
void taskSlave(void) {
	uint8_t buffer[2] = {0};
	//USART_Write(USART2, (uint8_t*) "TASKSLAVE READING ", 80);
	USART_Read(USART3, buffer, 2);
	//USART_Write(USART2, (uint8_t*) "TASKSLAVE GOT ", 80);
	//USART_Write(USART2, buffer, 2); // confirm the command
	//USART_Write(USART2, (uint8_t*) "\r\n", 80);
	
	if (buffer[0] == 'X') {
		USART_Write(USART2, (uint8_t*) "ENDGAME\r\n", 80);
		end_game();
	}
	
	if (buffer[0] != '$') {
		// set the command for player 1
		player1_com = buffer[0] - 48;
	}
	if (buffer[1] != '$') {
		// set the command for player 2
		player2_com = buffer[1] - 48;
		
		// write the command to the screen
		//USART_Clear(USART2);

		//USART_Write(USART2, buffer, 2);
		USART_Write(USART2, player2[gm][player2_com], 80);
	}
	
	while (player1_com < 250 && player2_com < 250) { // Loop until a player has done an input
		// Scan the keypad once		
		uint8_t key_pressed = 0;
		key_pressed = scan_key();
		if (key_pressed != 0) { // if a key press is detected
			if (key_pressed == player2_com + 48) { // if right key is pressed
				USART_Write(USART3, (uint8_t*) "$y", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 2!\r\n", 80);
				player2_com = 250;
				return;
			}
			else { // if wrong key is pressed
				USART_Write(USART3, (uint8_t*) "$n", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 2, INCORRECT TASK.\r\n", 80);
				player2_com = 250;
				return;
			}
		}
		
		// Check the button inputs
		
		if ((GPIOB->IDR | 0xFFFFFFFE) == 0xFFFFFFFE) { // red_btn_pressed PB0 
			while ((GPIOB->IDR | 0xFFFFFFFE) == 0xFFFFFFFE);
			if (player1_com == 0) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 1!\r\n", 80);
				player1_com = 250;
				return;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 1, INCORRECT TASK.\r\n", 80);
				player1_com = 250;
				return;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFF7) == 0xFFFFFFF7) { // blue btn is PB3
			while ((GPIOB->IDR | 0xFFFFFFF7) == 0xFFFFFFF7);
			if (player1_com == 1) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 1!\r\n", 80);
				player1_com = 250;
				return;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 1, INCORRECT TASK.\r\n", 80);
				player1_com = 250;
				return;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFFB) == 0xFFFFFFFB) { // green btn is PB2
			while ((GPIOB->IDR | 0xFFFFFFFB) == 0xFFFFFFFB);
			if (player1_com == 2) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 1!\r\n", 80);
				player1_com = 250;
				return;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 1, INCORRECT TASK.\r\n", 80);
				player1_com = 250;
				return;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFFFD) == 0xFFFFFFFD) { // yellow btn is PB1
			while ((GPIOB->IDR | 0xFFFFFFFD) == 0xFFFFFFFD);
			if (player1_com == 3) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 1!\r\n", 80);
				player1_com = 250;
				return;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 1, INCORRECT TASK.\r\n", 80);
				player1_com = 250;
				return;
			}
		}
		if ((GPIOB->IDR | 0xFFFFFDFF) == 0xFFFFFDFF) { // black is PB9
			while ((GPIOB->IDR | 0xFFFFFDFF) == 0xFFFFFDFF);
			if (player1_com == 4) {
				USART_Write(USART3, (uint8_t*) "y$", 2);
				USART_Write(USART2, (uint8_t*) "CORRECT, PILOT 1!\r\n", 80);
				player1_com = 250;
				return;
			}
			else {
				USART_Write(USART3, (uint8_t*) "n$", 2);
				USART_Write(USART2, (uint8_t*) "PILOT 1, INCORRECT TASK.\r\n", 80);
				player1_com = 250;
				return;
			}
		}
	} // while breakout loop
}

void end_game(void) {
	/*
	USART_Clear(USART2);
	uint8_t buffer[1] = {0};

	// break points into digits
	uint8_t pointage[3] = {'e', 'e', 'e'};
	
	uint8_t hundreds = points / (uint8_t) 100;
	points -= (100*hundreds);
	uint8_t tens = points / 10;
	uint8_t ones = points % 10;
	
	pointage[0] = hundreds + 48;
	pointage[1] = tens + 48;
	pointage[2] = ones + 48;
	
	//USART_Write(USART3, pointage, 3);
	
	USART_Write(USART2, (uint8_t*) "CONGARTULATIONS\r\n", 80);
	USART_Write(USART2, (uint8_t*) "YOUR SCORE IS\r\n", 80);
	USART_Write(USART2, pointage, 3);
	USART_Write(USART2, (uint8_t*) "POINTS!\r\n\r\n", 80);
	USART_Write(USART2, (uint8_t*) "RESET SLAVE THEN MASTER TO REPLAY\r\n", 80);
	
	while (1);*/
}
