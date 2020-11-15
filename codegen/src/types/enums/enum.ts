export class CANBusEnum<T extends string> {
  constructor(public readonly name: string, public readonly entries: T[]) {}

  get string() {
    const strings = [
      `enum struct ${this.name}: uint8_t {`,
      ...this.entries.map((entry, i) => `  ${entry} = ${i},`),
      `};`,
    ];
    return strings.join("\n");
  }
}
