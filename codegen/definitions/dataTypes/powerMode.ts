import { CANBusEnum } from "../../src/types/enums/enum";
import { CANBusDataType } from "../../src/types/datatypes/datatype";

export const powerModeEnum = new CANBusEnum("PowerMode", [
  "Idle",
  "HighPower",
  "LowPower",
  "MediumPower",
  "Hibernation",
]);

export const setPowerModeRequest_msg = new CANBusDataType(
  "SetPowerModeRequest",
  {
    mode: { type: "enum8", enum: powerModeEnum },
  }
);
