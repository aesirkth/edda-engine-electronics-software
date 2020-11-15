import { CANBusEnum } from "./types/enums/enum";
import { CANBusDataType } from "./types/datatypes/datatype";

export const encounteredEnums = new Set<CANBusEnum<any>>();
export const attachedMessages = new Set<CANBusDataType>();
export const attachedNames = new Map<number, string>();
