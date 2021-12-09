#include "stm32l476xx.h"
#include "TASK.h"
#include "TIM.h"
#include "USART.h"

uint8_t score;
int gm;
uint8_t p1Task;
uint8_t p2Task;

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
	{"Trigger the Bougeo!", "Start the Yezuom!", "Mobilize the Unoatu!", "Stabilize the Ehomawag!", "Toggle the Yyyogys!", "Stabilize the Bevaa!", "Start the Myoryuly!", "Start the Uhinowyawa!", "Start the Iruroj!", "Energize the Yqoywedoa!", "Activate the Inoyvoiy!", "Mobilize the Evahauniy!", "Push the Opicuiji!", "Trigger the Sezagyykiy!", "Stabilize the Ehiedenaow!", "Start the Xoulyzaty!"},
};

/*// Player 1 has the buttons
static uint8_t* player1[16] = { 
	"Press the red button ", // 0
	"Press the blue button ", // 1
	"Press the green button ", // 2
	"Press the yellow button ", // 3
	"Press the black button " // 4
};*/

// Player 2 has the keypad

// Task Master Function

void setGame(int x){
	gm = x;
	p1Task = (uint8_t) get_rand(4) + 48;
	p2Task = (uint8_t) get_rand(15) + 48;
}

void taskMaster(void){
	for(int i = 0; i < 50; i++)
		usart_delay();
	uint8_t task1 = p1Task;
	uint8_t task2 = p2Task;
	
	uint8_t buffer[2]; // store random tasks in buffer
	buffer[0] = task1;
	buffer[1] = task2;
	
	USART_Write(USART3, buffer, 2); // Send over the two instructions to scan
	
	//USART_Clear(USART2);
	USART_Write(USART2, player1[gm][task1 - 48], 80); // print player 1 instructions
	
	USART_Read(USART3, buffer, 2); // Wait for a response from the slave
	
	if (buffer[0] != '$'){
		if(buffer[0] == 'y'){
			USART_Write(USART2, (uint8_t*) " CORRECT, PILOT 1!\r\n", 80);
			p1Task = (uint8_t) get_rand(4) + 48;
			score++;
		} else {
			USART_Write(USART2, (uint8_t*) " PILOT 1, INCORRECT TASK.\r\n", 80);
			p1Task = (uint8_t) get_rand(4) + 48;
			p2Task = (uint8_t) get_rand(15) + 48;
		}
	}
	if (buffer[1] != '$') {
		if(buffer[1] == 'y'){
			USART_Write(USART2, (uint8_t*) " CORRECT, PILOT 2!\r\n", 80);
			p2Task = (uint8_t) get_rand(15) + 48;
			score++;
		} else {
			USART_Write(USART2, (uint8_t*) " PILOT 2, INCORRECT TASK.\r\n", 80);
			p1Task = (uint8_t) get_rand(4) + 48;
			p2Task = (uint8_t) get_rand(15) + 48;
		}
	}
}

void end_game(void) {
	USART_Clear(USART2);
	uint8_t pointage[3] = {'e', 'e', 'e'};
	
	uint8_t hundreds = score / (uint8_t) 100;
	score -= (100*hundreds);
	uint8_t tens = score / 10;
	uint8_t ones = score % 10;
	
	pointage[0] = hundreds + 48;
	pointage[1] = tens + 48;
	pointage[2] = ones + 48;
	
	//USART_Write(USART3, pointage, 3);
	
	USART_Write(USART2, (uint8_t*) "CONGARTULATIONS\r\n", 80);
	USART_Write(USART2, (uint8_t*) "YOUR SCORE IS\r\n", 80);
	USART_Write(USART2, pointage, 3);
	USART_Write(USART2, (uint8_t*) " POINTS!\r\n\r\n", 80);
	USART_Write(USART2, (uint8_t*) "RESET SLAVE THEN MASTER TO REPLAY\r\n", 80);
	while (1);
}