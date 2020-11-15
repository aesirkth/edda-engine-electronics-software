import { AbstractCodegenBlock } from "./block";
import { AbstractCodegenFile } from "./abstractFile";

export class CodegenFile extends AbstractCodegenFile {
  constructor(
    private readonly name: string,
    private readonly blocks: AbstractCodegenBlock[]
  ) {
    super(name);
  }

  getHeader() {
    return this.blocks.map((el) => el.getHeader()).join("\n");
  }

  getCode() {
    return this.blocks.map((el) => el.getCode()).join("\n");
  }
}
