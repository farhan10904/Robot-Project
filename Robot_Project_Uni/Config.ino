#include "Types.h"
bool SimMode = true;
Action LastTurn = Act_Left;
State CurrentState = FollowLine;
const int base = 150;
const int turn = 80;
const int reversebase = base / 2;
bool PrevIR_F = false;
bool PrevIR_R = false;
bool FrontSeenForPlate = false;
unsigned long FrontSeenTime = 0;
const unsigned long FrontTimeoutMS = 500;
int PlateHits = 0;
int DeliveriesDone = 0;
const int ignorePlates[] = {3,5};

int mr = 10;
int ml = 9;
int sl = 6;
int sc = 5;
int sr = 4;
int led = 13;
const int LineActiveLevel = LOW;
