import { AbstractCodegenBlock } from "./block";
import { indent } from "./util/indent";

export class CodegenNamespace extends AbstractCodegenBlock {
  constructor(
    readonly name: string,
    private readonly blocks: AbstractCodegenBlock[]
  ) {
    super();
  }

  getHeader() {
    const blocks = this.blocks
      .map((el) => el.getHeader())
      .filter((el) => el.trim().length > 0);
    if (blocks.length === 0) {
      return "";
    }

    return `namespace ${this.name} {
${indent(blocks.join("\n\n"))}
}`;
  }

  getCode() {
    const blocks = this.blocks
      .map((el) => el.getCode())
      .filter((el) => el.trim().length > 0);
    if (blocks.length === 0) {
      return "";
    }

    return `namespace ${this.name} {
${indent(blocks.join("\n\n"))}
}`;
  }
}
