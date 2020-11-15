import { CANBusDataType } from "../../src/types/datatypes/datatype";

export const timeSyncRequest_msg = new CANBusDataType("TimeSyncRequest", {
  source: { type: "id8" },
  requestIdentifier: { type: "uint16" },
  initiatedAtMicros: { type: "uint32" },
});

export const timeSyncResponse_msg = new CANBusDataType("TimeSyncResponse", {
  destination: { type: "id8" },
  requestIdentifier: { type: "uint16" },
  initiatedAtMicros: { type: "uint32" },
});
