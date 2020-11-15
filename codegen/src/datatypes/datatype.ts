import { CANBusMessageField } from "../fields/abstract";
import { Field } from "../fields/types";
import { CANBusMessageArrayField } from "../fields/array";
import { CANBusMessageScalarField } from "../fields/scalar";

export class CANBusMessageData {
  protected fields: CANBusMessageField[];

  constructor(readonly title: string, inputFields: Record<string, Field>) {
    this.fields = [];
    for (const name in inputFields) {
      const field = inputFields[name];
      if (field.type === "array") {
        this.fields.push(new CANBusMessageArrayField(name, field));
      } else {
        this.fields.push(new CANBusMessageScalarField(name, field));
      }
    }
  }

  get headerString() {
    const className = `${this.title}_Msg`;
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
    const className = `${this.title}_Msg`;
    let strings = [
      ...this.fields
        .flatMap((field) => field.publicSetters)
        .map(
          (str) =>
            `${str.replace(/^[A-z0-9]+(\s+)/g, (str, args) => {
              return `${str}${this.title}_Msg::`;
            })}`
        ),
      "",
      ...this.fields
        .flatMap((field) => field.publicGetters)
        .map(
          (str) =>
            `${str.replace(/^([A-z0-9]+)(\s+)/g, (str, args) => {
              return `${str}${this.title}_Msg::`;
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
