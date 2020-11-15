import { CANBusMessageField } from "./abstract";
import { CANBusMessageScalarField } from "./scalar";
import { ArrayField } from "./types";

export class CANBusMessageArrayField extends CANBusMessageField {
  scalarFields: CANBusMessageScalarField[];

  constructor(public readonly name: string, protected field: ArrayField) {
    super();

    this.scalarFields = [];

    for (let i = 0; i < this.field.count; i++) {
      this.scalarFields.push(
        new CANBusMessageScalarField(`${this.name}_${i}`, field.field)
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
