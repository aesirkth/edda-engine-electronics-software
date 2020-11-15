import { floatPackers, doublePackers } from "./src/types/utils/floatPack";
import { emitFiles } from "./src/codegen/emit/emit";
import { CodegenEnum } from "./src/codegen/emit/enum";
import { CodegenFile } from "./src/codegen/emit/file";
import { CodegenNamespace } from "./src/codegen/emit/namespace";
import { CodegenTextBlock } from "./src/codegen/emit/textBlock";
import { encounteredEnums, attachedMessages } from "./src/global";
import { rmdirSync } from "fs";
import {
  flightController_Node,
  controllerBoard_Node,
  telemetryBoard_Node,
  pressureBoard0_Node,
  pressureBoard1_Node,
} from "./definitions/nodes";
import {
  timeSyncResponse_msg,
  timeSyncRequest_msg,
} from "./definitions/dataTypes/time";
import { setPowerModeRequest_msg } from "./definitions/dataTypes/powerMode";
import { setDebugModeRequest_msg } from "./definitions/dataTypes/debugMode";
import { hello_msg } from "./definitions/dataTypes/chitchat";
import {
  typeKThermocouple_msg,
  coldJunctionTemperature_msg,
} from "./definitions/dataTypes/telemetry/thermocouple";
import { transducerPressure_msg } from "./definitions/dataTypes/telemetry/transducer";
import { attachMessages } from "./definitions/messages";
import { writeOutput } from "./src/emit";

attachMessages();
writeOutput();
