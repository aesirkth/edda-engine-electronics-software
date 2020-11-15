import { CANBusField } from "../fields/abstract";
import { Field } from "../fields/types";
import { CANBusArrayField } from "../fields/array";
import { CANBusScalarField } from "../fields/scalar";

export class CANBusDataType {
  protected fields: CANBusField[];

  constructor(readonly title: string, inputFields: Record<string, Field>) {
    this.fields = [];
    for (const name in inputFields) {
      const field = inputFields[name];
      if (field.type === "array") {
        this.fields.push(new CANBusArrayField(name, field));
      } else {
        this.fields.push(new CANBusScalarField(name, field));
      }
    }
  }

  get headerString() {
    const className = `${this.title}_DataType`;
    let strings = [
      `class alignas(8) ${className} {`,
      `  private:`,
      ...this.fields
        .flatMap((field) => field.privateFields)
        .map((str) => `    ${str};`),
      "",
      `  public:`,
      ...this.fields
        .flatMap((field) => field.publicFields)
        .map((str) => `    ${str};`),
      "",
      ...this.fields
        .flatMap((field) => field.publicSetterSignatures)
        .map((str) => `    ${str}`),
      "",
      ...this.fields
        .flatMap((field) => field.publicGetterSignatures)
        .map((str) => `    ${str}`),
      "",
      `};`,
      ``,
    ];

    return strings.join("\n");
  }

  get string() {
    const className = `${this.title}_DataType`;
    let strings = [
      ...this.fields
        .flatMap((field) => field.publicSetters)
        .map(
          (str) =>
            `${str.replace(/^[A-z0-9]+(\s+)/g, (str, args) => {
              return `${str}${this.title}_DataType::`;
            })}`
        ),
      "",
      ...this.fields
        .flatMap((field) => field.publicGetters)
        .map(
          (str) =>
            `${str.replace(/^([A-z0-9]+)(\s+)/g, (str, args) => {
              return `${str}${this.title}_DataType::`;
            })}`
        ),
      "",
      ...this.fields
        .flatMap((field) => field.staticAssignments ?? [])
        .map(
          (str) => `const ${str.type} ${className}::${str.name} = ${str.value};`
        ),
      ``,
      `static_assert((sizeof(${className}) <= 8), "sizeof(${className}) must be less than 8 bytes!");`,
      ``,
    ];

    return strings.join("\n");
  }
}
