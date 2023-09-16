#include "LedMatrixClockDisplay.h"

void LedMatrixClockDisplay::initialize() {
  if (!mx.begin()) {
    DEBUG_PRINTS("\nMD_MAX72XX initialization failed\n");
  } else {
    mx.control(MD_MAX72XX::INTENSITY, 0);
    mx.update(MD_MAX72XX::OFF);
    initialized = true;
  }
}

void LedMatrixClockDisplay::print(RTime time) {
  if (initialized) {
    mx.setBuffer(9 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getHour() / 10) + 1));
    mx.setBuffer(1 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getHour() / 10)));

    mx.setBuffer(10 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getHour() % 10) + 1));
    mx.setBuffer(2 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getHour() % 10)));

    mx.setBuffer(11 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getMinute() / 10) + 1));
    mx.setBuffer(3 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getMinute() / 10)));

    mx.setBuffer(12 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getMinute() % 10) + 1));
    mx.setBuffer(4 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (time.getMinute() % 10)));
    mx.transform(MD_MAX72XX::TRC);
  }
}

void LedMatrixClockDisplay::print(TemperatureAndHumidity value) {
  if (initialized) {
    mx.setChar((6 * COL_SIZE) - 1, '0' + ((int)value.getHumidity()) / 10);
    mx.setChar((7 * COL_SIZE) - 1, '0' + ((int)value.getHumidity()) % 10);
    mx.setChar((8 * COL_SIZE) - 1, '%');

    mx.setChar((14 * COL_SIZE) - 1, '0' + ((int)value.getTemperature()) / 10);
    mx.setChar((15 * COL_SIZE) - 1, '0' + ((int)value.getTemperature()) % 10);
    mx.setChar((16 * COL_SIZE) - 1, '0' + ((int)(value.getTemperature() * 10)) % 10);

    mx.setPoint(6, (15 * COL_SIZE) - 7, true);

    mx.setPoint(0, (16 * COL_SIZE) - 8, true);
    mx.setPoint(1, (16 * COL_SIZE) - 8, true);
    mx.setPoint(0, (16 * COL_SIZE) - 7, true);
    mx.setPoint(1, (16 * COL_SIZE) - 7, true);
  }
}
