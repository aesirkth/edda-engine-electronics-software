import { CANBusField } from "./abstract";
import { CANBusScalarField } from "./scalar";
import { ArrayField } from "./types";

export class CANBusArrayField extends CANBusField {
  scalarFields: CANBusScalarField[];

  constructor(public readonly name: string, protected field: ArrayField) {
    super();

    this.scalarFields = [];

    for (let i = 0; i < this.field.count; i++) {
      this.scalarFields.push(
        new CANBusScalarField(`${this.name}_${i}`, field.field)
      );
    }

    this.privateFields = this.scalarFields.flatMap(
      (field) => field.privateFields
    );
    this.publicFields = this.scalarFields.flatMap(
      (field) => field.publicFields
    );
    this.publicGetters = this.scalarFields.flatMap(
      (field) => field.publicGetters
    );
    this.publicSetters = this.scalarFields.flatMap(
      (field) => field.publicSetters
    );
    this.publicGetterSignatures = this.scalarFields.flatMap(
      (field) => field.publicGetterSignatures
    );
    this.publicSetterSignatures = this.scalarFields.flatMap(
      (field) => field.publicSetterSignatures
    );
    this.staticAssignments = this.scalarFields.flatMap(
      (field) => field.staticAssignments ?? []
    );
  }
}
