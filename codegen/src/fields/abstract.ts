export abstract class CANBusMessageField {
  privateFields: string[];
  publicFields: string[];
  publicSetters: string[];
  publicGetters: string[];
  publicSetterSignatures: string[];
  publicGetterSignatures: string[];
  staticAssignments?: {
    type: string;
    name: string;
    value: string;
  }[];
}
