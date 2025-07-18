# Fan-Controller
Simple 2 fan controller made with arduino leo from DFRobot and DS18B20


Jeep XJ Intelligent Fan Controller
Overview
This project solves a critical overheating issue on a 2001 Jeep Cherokee XJ during stop-and-go traffic. The issue is caused by the factory design, where the automatic transmission fluid (ATF) cooler sits on the cold side of the radiator, pre-heating coolant before it reaches the engine.

To address this, I designed a custom fan controller using a Beetle CM-32U4 microcontroller, a DS18B20 temperature sensor, and discrete NPN transistors to control a 3-fan shroud setup. The controller activates fans based on temperature thresholds to keep the engine operating around 210°F, even during slow driving.

Hardware Used
🧠 Beetle CM-32U4 Microcontroller
DFRobot Product Page

🌡️ DS18B20 Digital Temperature Sensor
DFRobot Product Page

🔋 5V 1.5A Linear Voltage Regulator
Adafruit Product Page

🔧 S8050 NPN Transistor Pack
DFRobot Product Page

🌬️ 3-Fan Shroud Radiator Assembly
Alloyworks Radiator and Fan Kit

Cooling System Improvements
Temperature Sensor Placement
The DS18B20 sensor is zip-tied to the fan on the hot side (AC auxiliary fan) to detect airflow temperature as it exits the ATF cooler and radiator stack.

Fan Activation Strategy

Each fan is activated based on temperature thresholds.

Fans are not PWM-controlled; a 5-second delay is implemented in the loop to prevent rapid switching of the S8050 transistors.

Transmission Cooler Upgrade

An external ATF cooler was mounted in front of the condenser, ensuring airflow priority before hitting the radiator.

Airflow order: ATF Cooler → AC Condenser → Radiator → Auxiliary Fan

Results
Highway Driving: No change needed — airflow is sufficient.

Street/Stop-Go: Engine coolant stays around 210°F, avoiding overheating.

Thermal Stack Optimization improves ATF and coolant temperature control by separating their heat load paths.

Future Improvements (Optional)
Add an OLED display or Bluetooth monitor.

Log temperature data to SD card.

Use MOSFETs with logic-level gate control for efficiency.

Make the thresholds configurable via serial or mobile UI.

License
MIT License
