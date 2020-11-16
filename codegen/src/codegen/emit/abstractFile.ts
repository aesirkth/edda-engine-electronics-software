import { relative, dirname, basename } from "path";

export abstract class AbstractCodegenFile {
  // Generate an import to a file
  private static generateImport(filename: string) {
    return `#include "${filename.replace(/\\/g, "/")}"`;
  }
  // Generate an import to a file
  private static generateBracketImport(filename: string) {
    return `#include <${filename.replace(/\\/g, "/")}>`;
  }

  constructor(readonly fileName: string) {}

  get header() {
    return this.getHeader();
  }

  get code() {
    return this.getCode();
  }

  protected abstract getHeader(): string;
  protected abstract getCode(): string;

  get headerFileContents() {
    const { imports, header } = this;

    return [
      "// Codegen file. Do not edit manually!",
      "",
      `#ifndef ${this.fileHeaderDefinitionName}`,
      `#define ${this.fileHeaderDefinitionName}`,
      "",
      imports,
      "",
      header,
      "",
      `#endif`,
    ].join("\n");
  }

  get codeFileContents() {
    const { imports, code } = this;

    const baseName = basename(`${this.fileName}.h`);
    return [
      "// Codegen file. Do not edit manually!",
      "",
      imports,
      AbstractCodegenFile.generateImport(baseName),
      "",
      code,
    ].join("\n");
  }

  get directoryName() {
    return dirname(this.fileName + ".h");
  }

  // Name that is used for the "#if !defined" block in the header file
  get fileHeaderDefinitionName() {
    const alphaNumericName = this.fileName
      .replace(/[^A-z]/g, "_")
      .toUpperCase()
      .replace(/^_+/, "")
      .replace(/_+$/, "")
      .replace(/_+/, "_");

    return `EDDA_${alphaNumericName}_H`;
  }

  get imports(): string {
    const codegenDependencies = this.dependencies.map((dependency) => {
      const relativePath = relative(
        this.directoryName,
        dependency.fileName + ".h"
      );

      return AbstractCodegenFile.generateImport(relativePath);
    });
    const fileDependencies = [...this.fileDependencies].map((dependency) =>
      AbstractCodegenFile.generateBracketImport(dependency)
    );

    return [...fileDependencies, ...codegenDependencies].join("\n");
  }

  readonly dependencies: AbstractCodegenFile[] = [];
  readonly fileDependencies = new Set<string>();

  addDependency(stringifier: AbstractCodegenFile): void;
  addDependency(filename: string): void;
  addDependency(stringifierOrFilename: AbstractCodegenFile | string) {
    if (typeof stringifierOrFilename === "string") {
      this.fileDependencies.add(stringifierOrFilename);
    } else {
      this.dependencies.push(stringifierOrFilename);
    }
  }
}
