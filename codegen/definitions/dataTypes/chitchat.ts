import { CANBusDataType } from "../../src/types/datatypes/datatype";
import { powerModeEnum } from "./powerMode";
import { debugModeEnum } from "./debugMode";

export const hello_msg = new CANBusDataType("Hello", {
  source: { type: "id8" },
  powerMode: { type: "enum8", enum: powerModeEnum },
  debugMode: { type: "enum8", enum: debugModeEnum },
});
