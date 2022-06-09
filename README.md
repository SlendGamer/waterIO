# Automatic Web-based Plant Watering System

**WaterIO** is a small private project to enable automatic watering of plants based on soil humidity. 

## Schematic

The application is structured as the diagram shows. The MCU (microcontroller unit) can handle different valves connected via a relay module. Each valve can consist of one or multiple watering zones and each zone can consist of one or multiple soil humidity sensors.

The graph is a spanning tree and may not be cyclic so that on child-element always has exactly one parent-element.

```mermaid
graph TB
  
  App[Application] --> P1[Pump1];
  App --> P2[Pump2];
  App --> PX[...];

  P1 --> V1[Valve 1];
  P1 --> V2[Valve 2];
  P1 --> VX[...];

  V1 --> Z1[Zone 1];
  V1 --> Z2[Zone 2];
  V1 --> ZX[...];

  Z1 --> Sen1[Sensor 1];
  Z1 --> Sen2[Sensor 2];
  Z1 --> SenX[...];
```
