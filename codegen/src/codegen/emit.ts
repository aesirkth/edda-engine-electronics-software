import { AbstractCodegenFile } from "./abstractFile";
import { join, dirname } from "path";
import { writeFileSync } from "fs";
import * as mkdirp from "mkdirp";

function* aggregateDependencies(
  stringifiers: AbstractCodegenFile[],
  visited: Set<AbstractCodegenFile>
): Iterable<AbstractCodegenFile> {
  for (const stringifier of stringifiers) {
    if (visited.has(stringifier)) {
      continue;
    }

    yield stringifier;
    visited.add(stringifier);

    for (const dependency of stringifier.dependencies) {
      yield* aggregateDependencies([dependency], visited);
    }
  }
}

export function emitFiles(
  directory: string,
  ...stringifiers: AbstractCodegenFile[]
) {
  const visited = new Set<AbstractCodegenFile>();
  for (const stringifier of aggregateDependencies(stringifiers, visited)) {
    const baseName = join(directory, stringifier.fileName);
    const headerFilename = `${baseName}.h`;
    const codeFilename = `${baseName}.cpp`;
    const directoryName = dirname(baseName);

    mkdirp.sync(directoryName);

    writeFileSync(headerFilename, stringifier.headerFileContents);
    writeFileSync(codeFilename, stringifier.codeFileContents);
  }
}
