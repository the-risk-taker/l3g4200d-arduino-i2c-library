/*
 * L3G4200D_.ino
 *
 * Created: 9/2/2018 11:02:21 AM
 * Author: Mateusz Patyk
 */ 

#include <Wire.h>

#include "Headers/Status.h"
#include "Headers/I2C_Sensor.h"
#include "Headers/L3G4200D.h"

static long previousTime		= 0;
long actualTime					= 0;

void setup()
{
	Wire.begin();
	
	Status.begin();
	Status.checkStatus(Gyroscope);
	
	// Set parameters or use defaults from L3G4200D::init()
	//		Gyroscope.setDataRateAndBandwidth(->your_setting<-);
	//		Gyroscope.setScale(->your_setting<-);
	
	// Disable low pass filtering
	//		Gyroscope.lowPassFilterSetting(DISABLE); // ENABLED by default
	
	// To perform calibration uncomment below:
	//		Gyroscope.performCalibrationProcedure();
	
	// Disable including calibration parameters into data
	//		Gyroscope.calibrationSetting(DISABLE); // ENABLED by default
}

void loop()
{
	actualTime = millis();
	
	if((actualTime - previousTime) >= 10)
	{
		Gyroscope.read();
		sFloatAxes scaled = Gyroscope.getScaled();
		sFloatAxes dps = Gyroscope.getTemporaryTraveledAngle();
		Status.printMessage("Angular Velocities:\tX = " + String(scaled.X) + 
							"\tY = " + String(scaled.Y) + 
							"\tZ = " + String(scaled.Z) + 
							"\tTemporary traveled angle:\tX = " + String(dps.X) +
							"\tY = " + String(dps.Y) +
							"\tZ = " + String(dps.Z)
		);
		previousTime = actualTime;
	}
}