import { CANBusEnum } from "./enums/enum";
import { CANBusMessageData } from "./datatypes/datatype";

export const encounteredEnums = new Set<CANBusEnum<any>>();
export const attachedMessages = new Set<CANBusMessageData>();
export const attachedNames = new Map<number, string>();
