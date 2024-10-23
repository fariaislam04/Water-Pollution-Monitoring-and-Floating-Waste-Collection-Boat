<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

<h1>IoT-Enabled Boat for Water Pollution Monitoring and Floating Waste Collection</h1>

<p>This project focuses on the design and implementation of an IoT-enabled boat to monitor water quality and collect floating waste in small water bodies. It integrates water quality sensors (TDS, turbidity, temperature) and a conveyor belt mechanism for waste collection, controlled via a mobile app. Data is transmitted to the Blynk IoT platform for real-time monitoring.</p>

<h2>Table of Contents</h2>
<ul>
    <li><a href="#introduction">Introduction</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#hardware-components">Hardware Components</a></li>
    <li><a href="#software">Software</a></li>
    <li><a href="#circuit-diagram">Circuit Diagram</a></li>
    <li><a href="#license">License</a></li>
</ul>

<h2 id="introduction">Introduction</h2>
<p>Water pollution poses a significant threat to ecosystems and human health. This project aims to provide an automated solution for collecting floating waste and monitoring water quality in real-time.</p>

<h2 id="features">Features</h2>
<ul>
    <li><strong>Water Quality Monitoring:</strong> Measures turbidity, Total Dissolved Solids (TDS), and temperature.</li>
    <li><strong>Waste Collection:</strong> Uses a conveyor belt mechanism to collect floating waste.</li>
    <li><strong>IoT Integration:</strong> Real-time monitoring via Blynk IoT platform.</li>
    <li><strong>Remote Control:</strong> Controlled through a mobile app using RF and Wi-Fi.</li>
</ul>

<h2 id="hardware-components">Hardware Components</h2>
<ul>
    <li>NodeMCU ESP32S x1</li>
    <li>L298N H-Bridge dual motor driver x1</li>
    <li>3v-9v Short shaft 180 DC motor x2</li>
    <li>Waterproof DS18B20 Digital thermal sensor x1</li>
    <li>Turbidity sensor: Suspension turbidity detection x1</li>
    <li>KS0429 TDS meter x1</li>
    <li>ESP-32 CAM Module x1</li>
    <li>6v TC DC Gear BO DC motor dual shaft x2</li>
    <li>3.7v Battery x6</li>
    <li>Breadboard</li>
    <li>PVC materials</li>
</ul>

<h2 id="software">Software</h2>
<ul>
    <li><strong>Arduino IDE:</strong> Programming the ESP32 microcontroller.</li>
    <li><strong>Blynk App:</strong> For IoT-based data visualization and boat control.</li>
    <li><strong>Fritzing:</strong> For creating the circuit diagram.</li>
</ul>

<h2 id="circuit-diagram">Circuit Diagram</h2>
<p><img src="https://i.ibb.co.com/Tbk4S08/Circuit-Diagram.png" alt="Circuit Diagram"></p>

<h2 id="license">License</h2>
<p>This project is licensed under the MIT License.</p>

</body>
</html>