
<p><img src="https://oxinon.com/wp-content/uploads/2019/02/IOTA-Vending-Machine-1.png" alt="Cover" width="400"></p>

Sell your product with IOTA and send the machine data to the Tangle.
<br>
<br>
<a href="https://ecosystem.iota.org/projects/iota-vending-machine">https://ecosystem.iota.org/projects/iota-vending-machine</a>
V0.01-BETA 

* * *

+ [Beschreibung](#german)
+ [Beschreibung der verwendeten Hardware](#hardware)
+ [Das Arduino-Yun](#arduinoyun)
+ [Aufbau der Elektronik](#elektronik)
***
+ [English description](#english) coming soon
+ [Hardware description](#harwareE) coming soon
+ [The Arduino-Yun](#arduinoyunE) coming soon
+ [Build up Elektronik](#elektronikE) coming soon

* * *
<a name="german"></a><h2>Beschreibung</h2>
Entwicklung und Bereitstellung eines Warenautomaten zum Verkauf verschiedener Waren und einfachen Bezahlung mit der Kryptowährung IOTA. Schwerpunkte hierbei sind der Aufbau der Hardware, die Entwicklung der Software zur Prozessabbildung der notwendigen Zahlungs-, Konfigurations- und Kontrollfunktionen sowie die Integration der notwendigen Hardwarekomponenten in die Prozessabläufe.
<br>
<br>
Basistechnologien: iota.js, mam.client.js, Node.js, React, C++, Linux (Ubuntu 18.04 LTS), Arduino


<a name="hardware"></a><h2>Beschreibung der verwendeten Hardware</h2>
Die Basis der Hardware des Automaten bildet ein MSI 98I6 Pico ITX mit einem Intel Pentium N4200 SoC QC bis zu 2,5Ghz, einer 64GB mPCI SSD Festplatte und einem Arbeitsspeicher von 4GB DDR4 RAM. Als Linux-Betriebssystem wird Ubuntu (aktuelle Version 18.04 LTS) eingesetzt. Für die Anzeige der Web-Applikation wird ein Chromium Browser im KIOSK-Modus verwendet. Der Programmstarter ist in der Datei `chromium-browser.desktop` definiert. Bei jedem Systemstart wird automatisch eine Internetverbindung mit dem 4G Modem Sierra MC7710 mPCI hergestellt. Die Bedienung des Automaten erfolgt über ein 7" Waveshare IPS-Touchscreen im Hochformat mit einer Auflösung von 1024 x 600 Pixel. 
Der wichtigste Part ist das Arduino-Yun Board, welches über die Ethernet Schnittstelle angesteuert wird. Die Kommunikation zwischen der Web-Applikation und der digitalen und analogen Ein- sowie Ausgänge des Arduino-Yun Board erfolgt IP-basierend über HTTP Requests.

<br>
Die folgende Grafik zeigt eine Übersicht der verwendeten Hardware:
<br>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/KomponentAll5.png" alt="Cover" width="500"></center></p>
(Quelle: siehe partlist.txt)
<hr>

<br>
<a name="arduinoyun"></a><h2>Das Arduino-Yun</h2>
Die Besonderheit des Arduino-Yun ist, dass dieser nicht nur ein Arduino-Subsystem basierend auf dem Mikrocontroller ATmega32u4 bereitstellt sondern zusätzlich auch ein Linux-Subsystem (LininoOS basierend auf Open-WRT) auf dem Atheros AR9331 SoC besitzt. Eine Bridge-Bibliothek ermöglicht die Kommunikation zwischen dem Linux- und dem Arduino-Subsystem.
Der USB-Port wird genutzt um die Software zur Ansteuerung der Elektronik zu installieren 
<br>
(siehe Datei `IOTA-Vending-Machine.ino`) und um die Debug-Informationen in einer seriellen Konsole auszugeben.
<br>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/BridgeBlockDiag-2.png" alt="Cover" width="500"></center></p>
(Quelle: arduino.cc)
<hr>
<br>
<a name="elektronik"></a><h2>Aufbau der Elektronik</h2>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/fritzing.png" alt="Cover" width="500"></center></p>
(Quelle: fritzing.org)
<hr>

<br>

