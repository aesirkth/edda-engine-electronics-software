export abstract class AbstractCodegenBlock {
  abstract getHeader(): string;
  abstract getCode(): string;
}
