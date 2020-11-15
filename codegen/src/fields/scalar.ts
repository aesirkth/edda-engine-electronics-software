import { CANBusMessageField } from "./abstract";
import { ScalarField } from "./types";
import { getNativeType } from "../types/getNativeType";
import { makePacker } from "../utils/floatPack";
import { encounteredEnums } from "../global";

export class CANBusMessageScalarField extends CANBusMessageField {
  readonly nativeType: string;
  readonly getSetType: string;

  constructor(public readonly name: string, protected field: ScalarField) {
    super();
    if (field.type === "enum8") {
      encounteredEnums.add(field.enum);
    }

    switch (this.field.type) {
      case "f32":
      case "f64":
        if (this.field.kind === "integerPacking") {
          this.nativeType = getNativeType(this.field.packInto);
        }
        if (this.field.kind === "nativePacking") {
          this.nativeType = getNativeType(this.field.type);
        }
        this.getSetType = getNativeType(this.field.type);
        break;
      case "enum8":
        this.nativeType = this.field.enum.name;
        this.getSetType = this.field.enum.name;
        break;
      default:
        this.nativeType = getNativeType(this.field.type);
        this.getSetType = getNativeType(this.field.type);
    }

    this.privateFields = [`${this.nativeType} ${this.name}`];

    switch (this.field.type) {
      case "f32":
      case "f64":
        if (this.field.kind === "integerPacking") {
          this.publicFields = [
            `static const ${this.getSetType} ${this.name}_minValue`,
            `static const ${this.getSetType} ${this.name}_maxValue`,
          ];
          this.staticAssignments = [
            {
              type: this.getSetType,
              name: `${this.name}_minValue`,
              value: this.field.minimumValue.toFixed(8),
            },
            {
              type: this.getSetType,
              name: `${this.name}_maxValue`,
              value: this.field.maximumValue.toFixed(8),
            },
          ];
        }
        break;

      default:
        this.publicFields = [];
        break;
    }

    const getterSignature = `${this.getSetType} get_${this.name}()`;

    switch (this.field.type) {
      case "f32":
      case "f64":
        if (this.field.kind === "integerPacking") {
          const { unpackName } = makePacker(
            this.field.type,
            this.field.packInto
          );
          this.publicGetterSignatures = [`${getterSignature};`];
          this.publicGetters = [
            `${getterSignature} {`,
            `  return ${unpackName}(${this.name}, ${this.name}_minValue, ${this.name}_maxValue);`,
            `}`,
          ];
          break;
        }
      default:
        this.publicGetterSignatures = [`${getterSignature};`];
        this.publicGetters = [
          `${getterSignature} {`,
          `  return ${this.name};`,
          `}`,
        ];
        break;
    }

    const setterSignature = `void set_${this.name}(${this.getSetType} value)`;

    switch (this.field.type) {
      case "f32":
      case "f64":
        if (this.field.kind === "integerPacking") {
          const { packName } = makePacker(this.field.type, this.field.packInto);
          this.publicSetterSignatures = [`${setterSignature};`];
          this.publicSetters = [
            `${setterSignature} {`,
            `  ${this.name} = ${packName}(value, ${this.name}_minValue, ${this.name}_maxValue);`,
            `}`,
          ];
          break;
        }
      default:
        this.publicSetterSignatures = [`${setterSignature};`];
        this.publicSetters = [
          `${setterSignature} {`,
          `  ${this.name} = value;`,
          `}`,
        ];
        break;
    }
  }
}
