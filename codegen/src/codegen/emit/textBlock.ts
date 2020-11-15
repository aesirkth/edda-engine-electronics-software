import { AbstractCodegenBlock } from "./block";

export class CodegenTextBlock extends AbstractCodegenBlock {
  constructor(private _header: string, private _block: string) {
    super();
  }

  getHeader(): string {
    return this._header;
  }
  getCode(): string {
    return this._block;
  }
}
