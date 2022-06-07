# Automatic Web-based Plant Watering System

**WaterIO** is a small private project to enable automatic watering of plants based on soil humidity. 

## Schematic

The application is structured as the diagram shows. The MCU (microcontroller unit) can handle different valves connected via a relay module. Each valve can consist of one or multiple watering zones and each zone can consist of one or multiple soil humidity sensors.

```mermaid
graph TD
  App[Application] --> V1[Valve 1];
  App --> V2[Valve 2];
  App --> VX[...];

  V1 --> Z1[Zone 1];
  V1 --> Z2[Zone 2];
  V1 --> ZX[...];
  V2 --> ZXX[...];

  Z1 --> Sen1[Sensor 1];
  Z1 --> Sen2[Sensor 2];
  Z1 --> SenX[...];
  Z2 --> SenXX[...];
```
