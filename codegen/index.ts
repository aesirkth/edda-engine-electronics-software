import { CANBusEnum } from "./src/enums/enum";
import { Field } from "./src/fields/types";
import { floatPackers, doublePackers } from "./src/utils/floatPack";
import { emitFiles } from "./src/codegen/emit";
import { CodegenEnum } from "./src/codegen/enum";
import { CodegenFile } from "./src/codegen/file";
import { CodegenNamespace } from "./src/codegen/namespace";
import { CodegenTextBlock } from "./src/codegen/textBlock";
import { CANBusMessageData } from "./src/datatypes/datatype";
import { encounteredEnums, attachedMessages } from "./src/global";
import { CANBusNode } from "./src/node/node";
import { rmdirSync } from "fs";

const timeSyncRequest_msg = new CANBusMessageData("TimeSyncRequest", {
  source: { type: "id8" },
  requestIdentifier: { type: "uint16" },
  initiatedAtMicros: { type: "uint32" },
});

const timeSyncResponse_msg = new CANBusMessageData("TimeSyncResponse", {
  destination: { type: "id8" },
  requestIdentifier: { type: "uint16" },
  initiatedAtMicros: { type: "uint32" },
});

const powerModeEnum = new CANBusEnum("PowerMode", [
  "Idle",
  "HighPower",
  "LowPower",
  "MediumPower",
  "Hibernation",
]);
const debugModeEnum = new CANBusEnum("DebugMode", ["Enabled", "Disabled"]);

const setPowerModeRequest_msg = new CANBusMessageData("SetPowerModeRequest", {
  mode: { type: "enum8", enum: debugModeEnum },
});

const setDebugModeRequest_msg = new CANBusMessageData("SetDebugModeRequest", {
  mode: { type: "enum8", enum: powerModeEnum },
});

const hello_msg = new CANBusMessageData("Hello", {
  source: { type: "id8" },
  powerMode: { type: "enum8", enum: powerModeEnum },
  debugMode: { type: "enum8", enum: debugModeEnum },
});

// Each reading is natively 14 bits of data
const typeKThermocoupleField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -270,
  maximumValue: 1372,
  packInto: "uint16",
};

const typeKThermocouple_msg = new CANBusMessageData(
  "MAX31850KHotJunctionData",
  {
    temperatures: {
      type: "array",
      count: 4,
      field: typeKThermocoupleField,
    },
  }
);

// Each reading is natively 12 bits of data
const max31850kColdJunctionField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -40,
  maximumValue: 125,
  packInto: "uint8",
};

const coldJunctionTemperature_msg = new CANBusMessageData(
  "MAX31850KColdJunctionData",
  {
    temperatures: {
      type: "array",
      count: 8,
      field: max31850kColdJunctionField,
    },
  }
);

// Each reading is natively 24 bits of data
const pressureTransducerField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: 0,
  maximumValue: 100e6, // 100 bars
  packInto: "uint32",
};

const transducerPressure_msg = new CANBusMessageData("TransducerPressures", {
  pressures: {
    type: "array",
    count: 2,
    field: pressureTransducerField,
  },
});

// Each reading is natively 24 bits of data
const ambientPressureField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: 0,
  maximumValue: 5e6, // 5 bars
  packInto: "uint32",
};

// Each reading is natively 24 bits of data
const ambientTemperatureField: Field = {
  type: "f32",
  kind: "integerPacking",
  minimumValue: -40,
  maximumValue: 85,
  packInto: "uint16",
};

const ambientPressure_msg = new CANBusMessageData("AmbientPressureSensorData", {
  pressure: ambientPressureField,
  temperature: ambientTemperatureField,
});

let nextId = 0x0;
const flightController = new CANBusNode(0);
const controllerBoard = new CANBusNode(1);
const telemetryBoard = new CANBusNode(2);
const pressureBoard0 = new CANBusNode(3);
const pressureBoard1 = new CANBusNode(4);

flightController.attachMessage(nextId++, timeSyncResponse_msg);
flightController.attachMessage(nextId++, setPowerModeRequest_msg);
flightController.attachMessage(nextId++, setDebugModeRequest_msg);

controllerBoard.attachMessage(nextId++, timeSyncRequest_msg);
telemetryBoard.attachMessage(nextId++, timeSyncRequest_msg);
pressureBoard0.attachMessage(nextId++, timeSyncRequest_msg);
pressureBoard1.attachMessage(nextId++, timeSyncRequest_msg);

controllerBoard.attachMessage(nextId++, hello_msg);
telemetryBoard.attachMessage(nextId++, hello_msg);
pressureBoard0.attachMessage(nextId++, hello_msg);
pressureBoard1.attachMessage(nextId++, hello_msg);

telemetryBoard.attachMessage(nextId++, typeKThermocouple_msg, "sensors_0_3");
telemetryBoard.attachMessage(nextId++, typeKThermocouple_msg, "sensors_4_7");
telemetryBoard.attachMessage(nextId++, coldJunctionTemperature_msg);

pressureBoard0.attachMessage(nextId++, transducerPressure_msg);
pressureBoard1.attachMessage(nextId++, transducerPressure_msg);

pressureBoard0.attachMessage(nextId++, ambientPressure_msg);
pressureBoard1.attachMessage(nextId++, ambientPressure_msg);

const packers: CodegenTextBlock[] = [];

for (const [, value] of [...floatPackers, ...doublePackers]) {
  packers.push(new CodegenTextBlock(value.packHeader, value.packDefinition));
  packers.push(
    new CodegenTextBlock(value.unpackHeader, value.unpackDefinition)
  );
}

rmdirSync("./output", {
  recursive: true,
});

const packFile = new CodegenFile("./packers", [
  new CodegenNamespace("EddaCAN", packers),
]);
packFile.addDependency("stdint.h");

const enums: CodegenEnum[] = [];
for (const enumVal of encounteredEnums) {
  enums.push(new CodegenEnum(enumVal.string));
}
const enumFile = new CodegenFile("./enums", [
  new CodegenNamespace("EddaCAN", enums),
]);

enumFile.addDependency("stdint.h");

const messageFiles: CodegenFile[] = [];

for (const msg of attachedMessages) {
  const file = new CodegenFile(`./messages/${msg.title}`, [
    new CodegenNamespace("EddaCAN", [
      new CodegenTextBlock(msg.headerString, msg.string),
    ]),
  ]);

  file.addDependency(enumFile);
  file.addDependency(packFile);
  file.addDependency("stdint.h");
  file.addDependency("limits.h");
  file.addDependency("string.h");

  messageFiles.push(file);
}

const rootFile = new CodegenFile("./index", []);
rootFile.addDependency(enumFile);
rootFile.addDependency(packFile);
for (const msgFile of messageFiles) {
  rootFile.addDependency(msgFile);
}

emitFiles("./output", enumFile, packFile, ...messageFiles, rootFile);

console.log("Emitted files");
