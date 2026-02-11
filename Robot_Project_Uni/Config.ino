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

const int mr = 10;
const int ml = 9;
const int sl = 6;
const int sc = 5;
const int sr = 4;
const int led = 13;
const int LineActiveLevel = LOW;

const int ForwardL = 8;
const int ReverseL = 7;
const int ForwardR = 12;
const int ReverseR = 11;
const int TriggerFront = 0;
const int ReceiveFront = 1;
const int TriggerRear = 2;
const int ReceiveRear = 3;

const int PlateDistanceThreshold = 15;
