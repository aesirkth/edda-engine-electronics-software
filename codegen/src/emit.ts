import { CodegenTextBlock } from "./codegen/emit/textBlock";
import { floatPackers, doublePackers } from "./types/utils/floatPack";
import { rmdirSync } from "fs";
import { CodegenFile } from "./codegen/emit/file";
import { CodegenNamespace } from "./codegen/emit/namespace";
import { CodegenEnum } from "./codegen/emit/enum";
import { encounteredEnums, attachedMessages } from "./global";
import { emitFiles } from "./codegen/emit/emit";

export function writeOutput() {
  const packers: CodegenTextBlock[] = [];

  for (const [, value] of [...floatPackers, ...doublePackers]) {
    packers.push(new CodegenTextBlock(value.packHeader, value.packDefinition));
    packers.push(
      new CodegenTextBlock(value.unpackHeader, value.unpackDefinition)
    );
  }

  rmdirSync("./output", {
    recursive: true,
  });

  const packFile = new CodegenFile("./packers", [
    new CodegenNamespace("EddaCAN", packers),
  ]);
  packFile.addDependency("stdint.h");

  const enums: CodegenEnum[] = [];
  for (const enumVal of encounteredEnums) {
    enums.push(new CodegenEnum(enumVal.string));
  }
  const enumFile = new CodegenFile("./enums", [
    new CodegenNamespace("EddaCAN", enums),
  ]);

  enumFile.addDependency("stdint.h");

  const messageFiles: CodegenFile[] = [];

  for (const msg of attachedMessages) {
    const file = new CodegenFile(`./messages/${msg.title}`, [
      new CodegenNamespace("EddaCAN", [
        new CodegenTextBlock(msg.headerString, msg.string),
      ]),
    ]);

    file.addDependency(enumFile);
    file.addDependency(packFile);
    file.addDependency("stdint.h");
    file.addDependency("limits.h");
    file.addDependency("string.h");

    messageFiles.push(file);
  }

  const rootFile = new CodegenFile("./index", []);
  rootFile.addDependency(enumFile);
  rootFile.addDependency(packFile);
  for (const msgFile of messageFiles) {
    rootFile.addDependency(msgFile);
  }

  emitFiles("./output", enumFile, packFile, ...messageFiles, rootFile);

  console.log("Emitted files");
}
