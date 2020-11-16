import {
  flightController_Node,
  controllerBoard_Node,
  telemetryBoard_Node,
  pressureBoard0_Node,
  pressureBoard1_Node,
} from "./nodes";
import {
  timeSyncLatencyResponse_msg,
  timeSyncTimeResponse_msg,
  timeSyncRequest_msg,
} from "./dataTypes/time";
import { setPowerModeRequest_msg } from "./dataTypes/powerMode";
import { setDebugModeRequest_msg } from "./dataTypes/debugMode";
import { hello_msg } from "./dataTypes/chitchat";
import {
  typeKThermocouple_msg,
  coldJunctionTemperature_msg,
} from "./dataTypes/telemetry/thermocouple";
import { transducerPressure_msg } from "./dataTypes/telemetry/transducer";
import { ambientPressureTemperature_msg } from "./dataTypes/telemetry/ambient";

export function attachMessages() {
  let nextId = 0x0;
  flightController_Node.attachMessage(nextId++, timeSyncRequest_msg);
  flightController_Node.attachMessage(nextId++, timeSyncTimeResponse_msg);
  flightController_Node.attachMessage(nextId++, timeSyncLatencyResponse_msg);
  flightController_Node.attachMessage(nextId++, setPowerModeRequest_msg);
  flightController_Node.attachMessage(nextId++, setDebugModeRequest_msg);

  controllerBoard_Node.attachMessage(nextId++, timeSyncRequest_msg);
  telemetryBoard_Node.attachMessage(nextId++, timeSyncRequest_msg);
  pressureBoard0_Node.attachMessage(nextId++, timeSyncRequest_msg);
  pressureBoard1_Node.attachMessage(nextId++, timeSyncRequest_msg);

  controllerBoard_Node.attachMessage(nextId++, hello_msg);
  telemetryBoard_Node.attachMessage(nextId++, hello_msg);
  pressureBoard0_Node.attachMessage(nextId++, hello_msg);
  pressureBoard1_Node.attachMessage(nextId++, hello_msg);

  telemetryBoard_Node.attachMessage(
    nextId++,
    typeKThermocouple_msg,
    "sensors_0_3"
  );
  telemetryBoard_Node.attachMessage(
    nextId++,
    typeKThermocouple_msg,
    "sensors_4_7"
  );
  telemetryBoard_Node.attachMessage(nextId++, coldJunctionTemperature_msg);

  pressureBoard0_Node.attachMessage(nextId++, transducerPressure_msg);
  pressureBoard1_Node.attachMessage(nextId++, transducerPressure_msg);

  pressureBoard0_Node.attachMessage(nextId++, ambientPressureTemperature_msg);
  pressureBoard1_Node.attachMessage(nextId++, ambientPressureTemperature_msg);
}
