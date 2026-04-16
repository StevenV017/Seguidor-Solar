# Seguidor-Solar
Este proyecto consiste en un sistema de control de lazo cerrado basado en el microcontrolador Arduino Uno. El objetivo es orientar un panel solar automáticamente hacia el punto de mayor intensidad lumínica para maximizar la eficiencia en la captación de irradiación solar directa durante el día.

**Descripción del proyecto**

El sistema resuelve el problema de la pérdida de eficiencia en paneles solares estáticos utilizando:

  - Detección: Uso de 4 fotorresistencias (LDR) colocadas en los cuatro extremos para medir la incidencia de luz.
  - Procesamiento: Un algoritmo en C++ que calcula promedios diferenciales para determinar la dirección del sol.
  - Actuación: Dos servomotores SG90 que ajustan la posición de la base en los ejes horizontal (azimut) y vertical (elevación).

**Requisitos e instalación**

*Hardware necesario*

  - 1x Arduino Uno R3 (ATmega328P).
  - 2x Servomotores SG90 o MG996R para obtener mayor torque.
  - 4x Fotorresistencias (LDR).
  - Estructura mecánica (madera o impresión 3D).

*Software y dependencias*

  - Arduino IDE (v1.8x o superior) o VS Code con la extensión PlatformIO.
  - Librería Servo.h incluida por defecto en el framework Arduino.

*Guía de instalación paso a paso*

  1. Clonar el repositorio:
     
  3. Conexión de hardware:
       - Servos: Conectar a los pines digitales D9 (azimut) y D10 (elevación).
       - LDRs: Configurar en puentes divisores hacia los pines analógicos A0, A1, A2 y A3.
  4. Carga de código:
       - Abre el archivo src/Codigo.txt o .ino en el IDE de Arduino.
       - Selecciona la placa "Arduino Uno".
       - Haz clic en "Subir (Upload)".

**Cómo usarlo**

Una vez cargado el código y alimentado el sistema:
  
  1. El sistema realizará un centrado inicial de los servos a 90º.
  2. Al detectar una fuente de luz, el panel se moverá grado a grado hacia el lado con mayor lectura.
  3. Tolerancia: El sistema ignora diferencias menores a 10 unidades para evitar vibraciones constantes.

**Estructura del proyecto**


