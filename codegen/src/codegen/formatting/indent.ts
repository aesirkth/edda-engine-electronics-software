export function indent(str: string) {
  const indentation = "  ";

  return (
    indentation +
    str.replace(/\n/g, "\n" + indentation).replace(/\n\s+\n/g, "\n\n")
  );
}
