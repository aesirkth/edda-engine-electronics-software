import { Field } from "../../../src/types/fields/types";
import { CANBusDataType } from "../../../src/types/datatypes/datatype";

// Each reading is natively 24 bits of data
const ambientPressureField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: 0,
  maximumValue: 5e6, // 5 bars
  packInto: "uint32",
};

// Each reading is natively 24 bits of data
const ambientTemperatureField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -40,
  maximumValue: 85,
  packInto: "uint16",
};

export const ambientPressureTemperature_msg = new CANBusDataType(
  "AmbientPressureTemperatureData",
  {
    pressure: ambientPressureField,
    temperature: ambientTemperatureField,
  }
);
