import { CANBusEnum } from "../../src/types/enums/enum";
import { CANBusDataType } from "../../src/types/datatypes/datatype";

export const debugModeEnum = new CANBusEnum("DebugMode", [
  "Enabled",
  "Disabled",
]);

export const setDebugModeRequest_msg = new CANBusDataType(
  "SetDebugModeRequest",
  {
    mode: { type: "enum8", enum: debugModeEnum },
  }
);
