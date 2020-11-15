import { Field } from "../../../src/types/fields/types";
import { CANBusDataType } from "../../../src/types/datatypes/datatype";

// Each reading is natively 24 bits of data
const pressureTransducerField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: 0,
  maximumValue: 100e6, // 100 bars
  packInto: "uint32",
};

export const transducerPressure_msg = new CANBusDataType(
  "TransducerPressures",
  {
    pressures: {
      type: "array",
      count: 2,
      field: pressureTransducerField,
    },
  }
);
