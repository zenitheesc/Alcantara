<h1 align="center" style="color:white; background-color:black">Alcantara</h1>
<h4 align="center"> Mobile Ground Station for stratospheric probe monitoring and rescue</h4>

<p align="center">
	<a href="http://zenith.eesc.usp.br/">
    <img src="https://img.shields.io/badge/Zenith-Embarcados-black?style=for-the-badge"/>
    </a>
    <a href="https://eesc.usp.br/">
    <img src="https://img.shields.io/badge/Linked%20to-EESC--USP-black?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/LICENSE">
    <img src="https://img.shields.io/github/license/zenitheesc/Alcantara_v.1.0?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/issues">
    <img src="https://img.shields.io/github/issues/zenitheesc/Alcantara_v.1.0?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/commits/experimental_realocate_components">
    <img src="https://img.shields.io/github/commit-activity/m/zenitheesc/Alcantara_v.1.0?style=for-the-badge">
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/zenitheesc/Alcantara_v.1.0?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/commits/experimental_realocate_components">
    <img src="https://img.shields.io/github/last-commit/zenitheesc/Alcantara_v.1.0?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/issues">
    <img src="https://img.shields.io/github/issues-raw/zenitheesc/Alcantara_v.1.0?style=for-the-badge" />
    </a>
    <a href="https://github.com/zenitheesc/Alcantara_v.1.0/pulls">
    <img src = "https://img.shields.io/github/issues-pr-raw/zenitheesc/Alcantara_v.1.0?style=for-the-badge">
    </a>
</p>

<p align="center">
    <a href="#environment-and-tools">Environment and Tools</a> •
    <a href="#Block-Diagram">Block Diagram</a> •
    <a href="#Schematic">Schematic</a> • 
    <a href="#Board">Board</a> • 
    <a href="#BOM">BOM</a> • 
    <a href="#Use-Concept">Use Concept</a>
</p>


The Alcantara board functions as a ground station and data hub for the probe flights .

It is equipped with a EBYTE E22-900M30S 30dB module that carries the Semtech SX1262 transceiver, capable of LoRa, (G)FSK and OOK. The packets received from the probe can then be sent via WiFi, Bluetooth or Serially to a host computer or mobile phone.

The onboard GNSS module carries the NEO-M8N from u-blox, enabling it to be used as a tracking device.

## Environment and tools

This system was designed using KiCad 5.1.10.

## Block Diagram

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Diagram.png"/>
</p>


## Schematic

The design was separated in hierarchical sheets to accommodate all components in an orderly way.

On the experimental_realocate_components sheet you can find the ESP32 WROOM Module, the SD Card module (connected via SPI), Boot and Reset button (with the Brownout prevention voltage supervisor), auto upload transistors and the external connector.

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Schematic_Page_1.png"/>
</p>


The second page contains the power section, with the TPS61092 Boost Converter (with another voltage supervisor for undervolting protection for the battery) for 5V, a 3.3V linear voltage regulator, the battery with a P channel mosfet for reverse voltage protection and a MAX17201G+T stand-alone fuel gauge for the 18650 battery voltage and current monitoring.

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Schematic_Page_2.png"/>
</p>

On the third page you find the Neo-M8N module from u-blox and the E22-900M30S module from EBYTE.

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Schematic_Page_3.png"/>
</p>

And the last page has the peripherals, the USB connector with its ESD protector, the RGB LED, the buzzer with its mosfet, the two user interface buttons and the USB to Serial Converter.

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Schematic_Page_4.png"/>
</p>


## Board

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Top.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Bottom.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Perspective1.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/Perspective2.png"/>
</p>


## Interactive BOM

https://htmlpreview.github.io/?https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/ibom.html

<!--
## Use concept

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/PhoneConcept.png"/>
</p>

<p align = "center">
<img src="https://github.com/zenitheesc/Alcantara_v.1.0/blob/experimental_realocate_components/Other_Files/Images/BoxConcept.png"/>
</p>


---

<p align="center">
    <a href="http://zenith.eesc.usp.br">
    <img src="https://img.shields.io/badge/Check%20out-Zenith's Oficial Website-black?style=for-the-badge" />
    </a> 
    <a href="https://www.facebook.com/zenitheesc">
    <img src="https://img.shields.io/badge/Like%20us%20on-facebook-blue?style=for-the-badge"/>
    </a> 
    <a href="https://www.instagram.com/zenith_eesc/">
    <img src="https://img.shields.io/badge/Follow%20us%20on-Instagram-red?style=for-the-badge"/>
    </a>

</p>
<p align = "center">
<a href="zenith.eesc@gmail.com">zenith.eesc@gmail.com</a>
</p>
-->