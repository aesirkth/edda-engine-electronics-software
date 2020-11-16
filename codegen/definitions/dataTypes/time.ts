import { CANBusDataType } from "../../src/types/datatypes/datatype";

export const timeSyncRequest_msg = new CANBusDataType("TimeSyncRequest", {
  source: { type: "id8" },
  requestIdentifier: { type: "uint8" },
  initiatedAtMillis: { type: "uint32" },
  initiatedAtMicros: { type: "uint16" },
});

export const timeSyncLatencyResponse_msg = new CANBusDataType(
  "TimeSyncLatencyResponse",
  {
    destination: { type: "id8" },
    requestIdentifier: { type: "uint8" },
    initiatedAtMillis: { type: "uint32" },
    initiatedAtMicros: { type: "uint16" },
  }
);

export const timeSyncTimeResponse_msg = new CANBusDataType(
  "TimeSyncTimeResponse",
  {
    destination: { type: "id8" },
    requestIdentifier: { type: "uint8" },
    responseMillis: { type: "uint32" },
    responseMicros: { type: "uint16" },
  }
);
