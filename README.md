# IOTA-Vending-Machine
IOTA-Vending-Machine, pay your Product with IOTA and send Machine data to the Tangle
<br>
V0.01-BETA 

* * *

+ [Beschreibung](#german)
+ [Beschreibung der verwendeten Hardware](#hardware)
+ [Das Arduino-Yun](#arduinoyun)
+ [Aufbau der Elektronik](#elektronik)
***
+ [English description](#english) coming soon
+ [Hardware description](#harwareE) coming soon
+ [The Arduino-Yun](#arduinoyunE)
+ [Build up Elektronik](#elektronikE) coming soon

* * *
<a name="german"></a><h2>Beschreibung</h2>
Entwicklung und Bereitstellung eines Warenautomaten zum Verkauf verschiedener Waren und einfachen Bezahlung mit der Kryptowährung IOTA. Schwerpunkte hierbei sind der Aufbau der Hardware, die Entwicklung der Software zur Prozessabbildung der notwendigen Zahlungs-, Konfigurations- und Kontrollfunktionen sowie die Integration der notwendigen Hardwarekomponenten in die Prozessabläufe.
<br>
Basistechnologien: iota.js, mam.client.js, Node.js, React, C++, Linux (Ubuntu 18.04 LTS), Arduino


<a name="hardware"></a><h2>Beschreibung der verwendeten Hardware</h2>
Als Node kommt ein MSI 98I6 Pico ITX zum Einsatz, dieser hat einen Intel Pentium N4200 SoC QC bis zu 2,5Ghz und 4GB RAM.
<br>
Ubuntu Linux ist auf der 64GB mPCI SSD Installiert, mit einem Chromium Brwoser der im Kiosk-Modus automatisch gestartet wird (chromium-browser.desktop)
<br>
Für die Automaten bedienung wird ein 7" Waveshare Touchscreen, mit einer auflösung 1024x600 IPS im Hochformat verwendet, in dem die zur verfühgng stehenden Produkte angezeigt werden, z.B. Kaugummi.
<br>
Für die nötige Internet Verbindung ist ein Sierra MC7710 mPCI 4G Modem verbaut, dieses stellt bei jedem startvorgang automatisch eine Verbindung mit dem Internet her.
<br>
Der wichtigste part ist das Arduino-Yun Board, dieses stellt die Verbindung mit hilfe einer Ethernet Schnitstelle her. Die Kommunikation zwischen der WEB-App und der Digitalen/Analogen Ein- und Ausgänge ist IP Basierend und arbeitet mit cURL HTTP request.
<br>
Die folgende Grafik zeigt eine Übersicht der verwendeten Hardware:
<br>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/KomponentAll5.png" alt="Cover" width="500"></center></p>
<hr>

<br>
<a name="arduinoyun"></a><h2>Das Arduino-Yun</h2>
Das Arduino-Yun ist besonders, da es nicht nur einen Microcontroler (ATmega32u4) sondern auch ein Linux auf dem Atheros AR9331 SoC besitzt (Linino basirend auf Open-WRT). Mit hilfe von der bridge library können die beiden Seiten mit einander Kommunizieren. 
<br>
Mit dem USB Prog. Port lässt sich nicht nur die Software aufspielen und Aktualisieren, die zur ansteuerung der Elektronik dient, sonder auch zum Debugen in einer Serielle Konsole.
<br>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/BridgeBlockDiag-2.png" alt="Cover" width="500"></center></p>
<hr>

<br>
<a name="elektronik"></a><h2>Aufbau der Elektronik</h2>
<p><center><img src="https://oxinon.com/wp-content/uploads/2019/02/fritzing.png" alt="Cover" width="500"></center></p>
<hr>
<br>

