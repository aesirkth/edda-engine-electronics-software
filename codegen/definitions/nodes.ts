import { CANBusNode } from "../src/types/nodes/node";

export const flightController_Node = new CANBusNode(0);
export const controllerBoard_Node = new CANBusNode(1);
export const telemetryBoard_Node = new CANBusNode(2);
export const pressureBoard0_Node = new CANBusNode(3);
export const pressureBoard1_Node = new CANBusNode(4);
