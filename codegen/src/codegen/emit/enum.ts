import { AbstractCodegenBlock } from "./block";

export class CodegenEnum extends AbstractCodegenBlock {
  constructor(private readonly stringValue: string) {
    super();
  }

  getHeader() {
    return this.stringValue;
  }

  getCode() {
    return "";
  }
}
