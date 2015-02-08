#include "cBoiler.h"

cBoiler::cBoiler(cRooms* Rooms_,cWarmWater* WarmWater_)
:Valve(PinValveBoilerOpen,PinValveBoilerClose),
pid( 1.05, 0.0, 10.5, REVERSE), //I= 0.063
TempCharge((&MPNumSys[0]),(&MPChanSys[idxTempBoilerCharge]),(&SysTempOffset[idxTempBoilerCharge])),
TempReserve1((&MPNumSys[0]),(&MPChanSys[idxTempBoilerReserve1]),(&SysTempOffset[idxTempBoilerReserve1])),
TempReserve2((&MPNumSys[0]),(&MPChanSys[idxTempBoilerReserve2]),(&SysTempOffset[idxTempBoilerReserve2])),
TempHead((&MPNumSys[0]),&MPChanSys[idxTempBoilerHead],(&SysTempOffset[idxTempBoilerHead])),
TempTop((&MPNumSys[0]),&MPChanSys[idxTempBoilerTop],(&SysTempOffset[idxTempBoilerTop])),
Pump(PinPumpBoiler)
{
	Rooms = Rooms_;
	WarmWater = WarmWater_;
	ChargeMargin = DefaultChargeMargin;
	// Set minimal Pump Power to 10%
	pid.SetOutputLimits(0.1, 1);
}

void cBoiler::getSP( JsonObject& root )
{
  //char p_buffer[80];
	//root[P("Bcm")] = ChargeMargin;
	root["Bcm"] = ChargeMargin;
}

int cBoiler::setSP( JsonObject& root )
{
	int fail = 0;
	int posReturn =0;
	
	if(root.containsKey("Bcm")) {
		if(root["Bcm"].is<double>()) {
			ChargeMargin = root["Bcm"].as<double>();
			posReturn++;
		}
		else fail=1;
	}
	else fail=1;
	
	if (fail == 0) // If all three parameter objects were successfully filled
	return posReturn;
	else
	return 0;
}

void cBoiler::getData( JsonObject& root )
{
	//char buffer[30];
	//PROGMEM prog_char  BoilerValve[]  = "BoilerValve";
	//strcpy_P(buffer, (char*)pgm_read_word(&(sBoilerValve)));
	root["BV"] =  static_cast<int>( Valve.get());

	root["BT0"] = TempCharge.get();
	root["BT1"] = TempTop.get();
	root["BT2"] = TempHead.get();
	root["BT3"] = TempReserve1.get();
	root["BT4"] = TempReserve2.get();
	
	root["BP"] =  pid.get();
	root["BncW"] =  static_cast<int>( bneedChargeWarmWater);
	root["BncH"] =  static_cast<int>( bneedChargeHeating);
	root["Bdisc"] =  static_cast<int>( bDischarging);
	root["Bc"] =  static_cast<int>( bCharging);
	root["BTsW"] =  WarmWater->SpTemp();
	root["BTsc"] =   getSpTempCharge();
}