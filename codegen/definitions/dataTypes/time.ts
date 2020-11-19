import { CANBusDataType } from "../../src/types/datatypes/datatype";

export const timeSyncRequest_msg = new CANBusDataType("TimeSyncRequest", {
  source: { type: "id8" },
  requestIdentifier: { type: "uint8" },
  currentMicros: { type: "uint32" },
});

export const timeSyncLatencyResponse_msg = new CANBusDataType(
  "TimeSyncLatencyResponse",
  {
    destination: { type: "id8" },
    requestIdentifier: { type: "uint8" },
    initiatorMicros: { type: "uint32" },
  }
);

export const timeSyncTimeResponse_msg = new CANBusDataType(
  "TimeSyncTimeResponse",
  {
    destination: { type: "id8" },
    requestIdentifier: { type: "uint8" },
    bits0through31: { type: "uint32" },
    bits32through47: { type: "uint16" },
  }
);
