import { CANBusEnum } from "../enums/enum";

export type FloatingPointFieldType = "f32" | "f64";
export type UnsignedIntegerFieldType = "uint8" | "uint16" | "uint32" | "uint64";
export type SignedIntegerFieldType = "int8" | "int16" | "int32" | "int64";
export type IntegerFieldType =
  | UnsignedIntegerFieldType
  | SignedIntegerFieldType;
export type IDFieldtype = "id8";
export type EnumFieldType = CANBusEnum<any>;

export type ScalarField =
  | {
      type: FloatingPointFieldType;
      kind: "nativePacking";
    }
  | {
      type: FloatingPointFieldType;
      kind: "integerPacking";
      packInto: UnsignedIntegerFieldType;
      minimumValue: number;
      maximumValue: number;
    }
  | {
      type: IntegerFieldType;
    }
  | {
      type: IDFieldtype;
    }
  | {
      type: "enum8";
      enum: EnumFieldType;
    };

export type ArrayField = {
  type: "array";
  count: number;
  field: ScalarField;
};

export type Field = ScalarField | ArrayField;
