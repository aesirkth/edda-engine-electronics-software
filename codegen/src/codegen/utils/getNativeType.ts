import {
  FloatingPointFieldType,
  UnsignedIntegerFieldType,
  SignedIntegerFieldType,
  IDFieldtype,
} from "../../types/fields/types";

export function getNativeType(
  type:
    | FloatingPointFieldType
    | UnsignedIntegerFieldType
    | SignedIntegerFieldType
    | IDFieldtype
) {
  switch (type) {
    case "id8":
      return "uint8_t";
    case "f32":
      return "float";
    case "f64":
      return "double";
    case "int8":
      return "int8_t";
    case "int16":
      return "int16_t";
    case "int32":
      return "int32_t";
    case "int64":
      return "int64_t";
    case "uint8":
      return "uint8_t";
    case "uint16":
      return "uint16_t";
    case "uint32":
      return "uint32_t";
    case "uint64":
      return "uint64_t";
    default:
      throw new Error("Unknown type: " + type);
  }
}
