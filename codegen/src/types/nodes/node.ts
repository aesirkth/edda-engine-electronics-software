import { CANBusDataType } from "../datatypes/datatype";
import { attachedMessages, attachedNames } from "../../global";

export class CANBusNode {
  constructor(id: number);
  constructor(readonly id: number) {}

  attachMessage(
    messageId: number,
    message: CANBusDataType,
    namePostfix?: string
  ) {
    attachedMessages.add(message);
    attachedNames.set(messageId, `${message.title}${namePostfix ?? ""}`);
  }
}
