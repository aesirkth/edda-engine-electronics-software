import { CANBusDataType } from "../../../src/types/datatypes/datatype";
import { Field } from "../../../src/types/fields/types";

// Each reading is natively 14 bits of data
const typeKThermocoupleField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -270,
  maximumValue: 1372,
  packInto: "uint16",
};

export const typeKThermocouple_msg = new CANBusDataType(
  "MAX31850KHotJunctionData",
  {
    temperatures: {
      type: "array",
      count: 4,
      field: typeKThermocoupleField,
    },
  }
);

// Each reading is natively 12 bits of data
const max31850kColdJunctionField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -40,
  maximumValue: 125,
  packInto: "uint8",
};

export const coldJunctionTemperature_msg = new CANBusDataType(
  "MAX31850KColdJunctionData",
  {
    temperatures: {
      type: "array",
      count: 8,
      field: max31850kColdJunctionField,
    },
  }
);
