import {
  UnsignedIntegerFieldType,
  FloatingPointFieldType,
} from "../fields/types";
import { getNativeType } from "../../codegen/utils/getNativeType";

export type Packer = {
  packName: string;
  unpackName: string;
  packDefinition: string;
  unpackDefinition: string;
  packHeader: string;
  unpackHeader: string;
};
export const floatPackers = new Map<UnsignedIntegerFieldType, Packer>();
export const doublePackers = new Map<UnsignedIntegerFieldType, Packer>();

export function makePacker(
  floatingPointType: FloatingPointFieldType,
  packInto: UnsignedIntegerFieldType
) {
  let map: Map<UnsignedIntegerFieldType, Packer>;
  if (floatingPointType === "f32") {
    map = floatPackers;
  } else if (floatingPointType === "f64") {
    map = doublePackers;
  } else {
    throw new Error(`Unknown floating point type '${floatingPointType}'`);
  }

  if (map.has(packInto)) {
    return map.get(packInto)!;
  }

  let nativeType = getNativeType(floatingPointType);
  const packType = getNativeType(packInto);
  const packName = `pack_${nativeType}_into_${packType}`;
  const unpackName = `unpack_${packType}_into_${nativeType}`;

  let maxType: string = "(1)";
  switch (packType) {
    case "uint8_t":
      maxType = "UINT8_MAX";
      break;
    case "uint16_t":
      maxType = "UINT16_MAX";
      break;
    case "uint32_t":
      maxType = "UINT32_MAX";
      break;
    case "uint64_t":
      maxType = "UINT64_MAX";
      break;
  }

  const packDefinition = `inline ${packType} pack_float_into_${packType}(float value, const float minValue, const float maxValue) {
  if(value < minValue) { return 0; }
  if(value > maxValue) { return ${maxType}; }

  float ratio = ((float) value - minValue) / (maxValue - minValue);
  return 1 + (${packType}) ((float) (${maxType} - 2)) * ratio;
}`;

  const unpackDefinition = `inline float unpack_${packType}_into_float(${packType} value, const float minValue, const float maxValue) {
  if(value <= 0) {
    return minValue - 1.0;
  }
  if(value >= ${maxType}) {
    return maxValue + 1.0;
  }

  float ratio = (float)(value - 1) / (float) (${maxType} - 2);
  return ratio * (maxValue - minValue) + minValue;
}`;

  const packHeader = `${packType} pack_float_into_${packType}(float value, const float minValue, const float maxValue);`;
  const unpackHeader = `float unpack_${packType}_into_float(${packType} value, const float minValue, const float maxValue);`;

  const returnType: Packer = {
    packName,
    unpackName,
    packDefinition,
    unpackDefinition,
    packHeader,
    unpackHeader,
  };
  map.set(packInto, returnType);

  return returnType;
}
